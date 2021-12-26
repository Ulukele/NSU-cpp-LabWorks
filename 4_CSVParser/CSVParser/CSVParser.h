#pragma once

#include <vector>
#include <tuple>
#include <iostream>
#include <sstream>
#include "../Exceptions/TableItemException.h"

namespace {

    template<class T>
    bool convert(const std::string &column, T& out) {
        std::istringstream stream(column);
        stream >> out;
        return true;
    }

    template<size_t I, class... Args>
    struct reader {
        static int read(std::vector<std::string>& columns, std::tuple<Args...> &t) {
            int readed = reader<I - 1, Args...>::read(columns, t);
            if (columns.size() <= I) {
                return readed;
            }
            convert(columns[I], std::get<I>(t));
            return readed + 1;
        }
    };

    template<class... Args>
    struct reader<0, Args...> {
        static int read(std::vector<std::string>& columns, std::tuple<Args...>& t) {
            if (columns.empty()) {
                return 0;
            }
            convert(columns[0], std::get<0>(t));
            return 1;
        }
    };

    template<class... Args>
    int read_tuple(std::istream& is, std::tuple<Args...>& t, char row_delimiter, char col_delimiter) {
        std::string row;
        std::getline(is, row, row_delimiter);
        std::istringstream row_stream(row);

        std::vector<std::string> columns;
        while (row_stream.peek() != EOF) {
            std::string column;
            std::getline(row_stream, column, col_delimiter);
            columns.push_back(column);
        }

        return reader<sizeof...(Args) - 1, Args...>::read(columns, t);
    }
}

template<class... Args>
class CSVParser {
public:

    CSVParser(
            std::istream& instream,
            int skip_lines,
            char row_delimiter='\n', // default delimiter
            char col_delimiter=','   // default delimiter
    ):
    instream(instream),
    skip_lines(skip_lines),
    row_delimiter(row_delimiter),
    col_delimiter(col_delimiter) {
        std::tuple<Args...> t;
        for (int i = 0 ; i < skip_lines; ++i) {
            read_tuple(instream, t, row_delimiter, col_delimiter);
        }
        skip_count = (int)(instream.tellg());
        instream.seekg(0);
    }

    class iterator
    {
        CSVParser<Args...>* obj_;
        int count;
        int lines;
        std::tuple<Args...> current_;
    public:
        using value_type = std::tuple<Args...>;
        using reference = const std::tuple<Args...>&;
        using pointer = const std::tuple<Args...>*;
        using iterator_category = std::input_iterator_tag;

        iterator(CSVParser<Args...>* obj): obj_(obj) {
            if (obj_ != nullptr) {
                lines = obj_->skip_lines;
                count = obj_->skip_count;
                increment();
            }
        }

        reference operator*() const {
            return current_;
        }

        iterator& operator++() {
            increment(); return *this;
        }

        iterator operator++(int) {
            increment(); return *this;
        }

        bool operator==(iterator rhs) const {
            return (obj_ == rhs.obj_ && (obj_ == nullptr || count == rhs.count));
        }

        bool operator!=(iterator rhs) const {
            return !(rhs == *this);
        }

    protected:
        void increment() {
            if (!valid(count)) {
                obj_ = nullptr;
                return;
            }
            lines++;
            next(current_, count);
        }
        void next(std::tuple<Args...>& t, int& skip_c) {
            obj_->instream.seekg(skip_c);
            int readed_count = read_tuple(obj_->instream, t, obj_->row_delimiter, obj_->col_delimiter);
            if (readed_count < sizeof...(Args)) {
                throw Exceptions::TableItemException(lines, readed_count + 1);
            }
            skip_c = obj_->instream.tellg();
            obj_->instream.seekg(0);
        }

        bool valid(int skip_c) const {
            if (obj_ == nullptr) return false;
            obj_->instream.seekg(skip_c);
            bool status = obj_->instream.peek() != EOF;
            obj_->instream.seekg(0);
            return status;
        }
    };

    iterator begin() {
        return iterator{this};
    }

    iterator end() {
        return iterator{nullptr};
    }

    ~CSVParser() = default;

private:
    std::istream& instream;
    int skip_lines;
    int skip_count;
    char row_delimiter;
    char col_delimiter;

};

