#pragma once

#include <vector>
#include <tuple>
#include <iostream>
#include <sstream>

namespace {

    template<class T>
    bool convert(const std::string &column, T& out) {
        std::istringstream stream(column);
        stream >> out;
        return true;
    }

    template<size_t I, class... Args>
    struct delimiter_reader {
        static bool read_with_delimiter(std::istream& is, std::tuple<Args...> &t, char delimiter) {
            std::string buff;
            if (is.peek() == EOF) return false;
            getline(is, buff, delimiter);
//            if (buff[buff.size() - 1] != delimiter) return false;
            return convert(buff, std::get<I>(t));
        }
    };

    template<size_t I, class... Args>
    struct reader {
        static bool read(std::istream &is, std::tuple<Args...> &t, char delimiter) {
            reader<I - 1, Args...>::read(is, t, delimiter);
            return delimiter_reader<I, Args...>::read_with_delimiter(is, t, delimiter);
        }
    };

    template<class... Args>
    struct reader<0, Args...> {
        static bool read(std::istream& is, std::tuple<Args...>& t, char delimiter) {
            return delimiter_reader<0, Args...>::read_with_delimiter(is, t, delimiter);
        }
    };

    template<size_t I, class... Args>
    struct reader_ {
        static bool read(std::istream &is, std::tuple<Args...> &t, char row_delimiter, char col_delimiter) {
            reader<I - 1, Args...>::read(is, t, col_delimiter);
            return delimiter_reader<I, Args...>::read_with_delimiter(is, t, row_delimiter);
        }
    };

    template<class... Args>
    bool read_tuple(std::istream& is, std::tuple<Args...>& t, char row_delimiter, char col_delimiter) {
        return reader_<sizeof...(Args) - 1, Args...>::read(is, t, row_delimiter, col_delimiter);
    }
}

template<class... Args>
class CSVParser {
public:

    CSVParser(
            std::istream& instream,
            size_t skip_lines,
            char row_delimiter='\n', // default delimiter
            char col_delimiter=','   // default delimiter
    ):
    instream(instream),
    skip_lines(skip_lines),
    row_delimiter(row_delimiter),
    col_delimiter(col_delimiter) {}

    size_t GetSkipLines() { return skip_lines; }

    class iterator
    {
        CSVParser<Args...>* obj_;
        size_t skip_lines;
        std::tuple<Args...> current_;
    public:
        using value_type = std::tuple<Args...>;
        using reference = const std::tuple<Args...>&;
        using pointer = const std::tuple<Args...>*;
        using iterator_category = std::input_iterator_tag;
        iterator(size_t skip_lines, CSVParser<Args...>* obj=nullptr): obj_(obj), skip_lines(skip_lines) {
            if (obj_ != nullptr) {
                for (size_t i = 0; i <= skip_lines; ++i) {
                    obj_->next(current_);
                }
            }
        }
        reference operator*() const { return current_; }
        iterator& operator++() { increment(); return *this; }
        iterator operator++(int) { increment(); return *this; }
        bool operator==(iterator rhs) const { return obj_ == rhs.obj_; }
        bool operator!=(iterator rhs) const { return !(rhs == *this); }
    protected:
        void increment() {
            if (!obj_->valid()) {
                obj_ = nullptr;
                return;
            }
            skip_lines++;
            obj_->next(current_);
        }
    };
    iterator begin() { return iterator{skip_lines, this}; }
    iterator end() { return iterator{skip_lines}; }

    void next(std::tuple<Args...>& t) {
        read_tuple(instream, t, row_delimiter, col_delimiter);
    }

    bool valid() const {
        return instream.peek() != EOF;
    }

    ~CSVParser() = default;

private:
    std::istream& instream;
    size_t skip_lines;
    char row_delimiter;
    char col_delimiter;

};

