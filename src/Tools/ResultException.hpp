/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** 05
*/

#ifndef RESULTEXCEPTION_HPP
    #define RESULTEXCEPTION_HPP

#include <variant>
#include "plazza.hpp"

namespace Plazza {
    template <typename T>
    class ResultException {
        std::variant<T, std::exception_ptr> _data; ///> Variant to store either the result or an exception
        bool _hasValue; ///> Flag to indicate if the result is valid
    public:
        /**
         * Constructor to initialize the ResultException with a valid result.
         * @param value The result value
         */
        explicit ResultException(const T& value) : _data(value), _hasValue(true) {}

        /**
         * Constructor to initialize the ResultException with an exception.
         * @param value The exception pointer
         */
        explicit ResultException(const std::exception_ptr& value) : _data(value), _hasValue(false) {}

        /**
         * If the result is valid, return the result value bool.
         * @return The result value boolean
         */
        [[nodiscard]] bool hasValue() const { return _hasValue; }

        /**
         * Gets the result value if it is valid.
         * @return The result value
         * @throws std::exception if the result is not valid
         */
        T getValue() const
        {
            if (_hasValue)
                return std::get<T>(_data);
            std::rethrow_exception(std::get<std::exception_ptr>(_data));
        }

        /**
         * Gets the ErrorMessage if the result is not valid.
         * @return The error message
         * @throws std::exception if the result is valid
         */
        [[nodiscard]] std::string getErrorMessage() const
        {
            if (this->hasValue())
                return "";
            try {
                std::rethrow_exception(std::get<std::exception_ptr>(_data));
            } catch (const std::exception& e) {
                return e.what();
            } catch (...) {
                return "Unknown error";
            }
        };

        /**
         * If the result is not valid, return false;
         * @return The error message boolean
         */
        bool hasErrorMessage() const { return !_hasValue; }
    };

    /**
     * Function to handle exceptions and return a ResultException object.
     * @param func The function to call
     * @param args The arguments to pass to the function
     * @tparam Func The type of the function
     * @tparam Args The types of the arguments
     * @return A ResultException object containing the result or an exception
     * @note Provide the return type to auto with the ->
     * @note This function is used to handle exceptions in a generic way. This function does not work with void functions.
     * @note It is used to wrap the function call in a try-catch block and return a ResultException object.
     * @note The function can be any callable object, such as a lambda or a function pointer.
     */
    template <typename Func, typename... Args>
    auto handleExceptions(Func&& func, Args&&... args) -> ResultException<decltype(func(args...))>
    {
        using RetResult = decltype(func(args...));

        try {
            return ResultException<RetResult>(func(std::forward<Args>(args)...));
        } catch (...) {
            return ResultException<RetResult>(std::current_exception());
        }
    }
}

#endif // RRESULTEXCEPTION_HPP