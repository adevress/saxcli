/**
 * Copyright (c) 2024, Adrien Devresse <adev@adev.name>
 *
 * Boost Software License - Version 1.0
 *
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */
#pragma once

#include <bitset>
#include <functional>
#include <string_view>
#include <vector>
#include <stdexcept>

namespace saxcli {


class option;
class sub_command;
class options_handler;
struct options_format;

///
/// \brief generic error for error parsing
///
class parse_options_error : public std::runtime_error {
  public:
    explicit inline parse_options_error(const std::string& msg) : std::runtime_error(msg) {}
    explicit inline parse_options_error(const std::string& msg, std::vector<std::string> subcmd)
        : std::runtime_error(msg), _subcmds(subcmd) {}


    inline const std::vector<std::string>& subcommand_stack() const { return _subcmds; }


  private:
    std::vector<std::string> _subcmds;
};


///
/// \brief parameter subcommand
///
class options_handler {
  public:
    enum class flag { only_subcmd = 0, no_help = 1 };

    // help format
    struct help_format {
        help_format() : margin(2), padding(2) {}
        std::size_t margin;
        std::size_t padding;
    };

    options_handler(std::string name, std::string help_msg);

    options_handler(const options_handler&) = default;
    options_handler(options_handler&&) = default;

    options_handler& operator=(const options_handler&) = default;
    options_handler& operator=(options_handler&&) = default;

    /// add an option to the option handler
    void add_option(option opt);

    /// add a subcommand with its own set of options to the handler
    void add_subcommand(sub_command sub_com);

    /// add a positional argument handler
    void set_positional_argument_handler(std::function<void(const std::string&)> handler);

    /// set a flag
    void set_flags(flag f, bool v);

    bool get_flag(flag f) const;


    const std::vector<sub_command>& sub_commands() const;

    const std::vector<option>& options() const;


    std::string help(const help_format& fmt = help_format()) const;

    std::string_view name() const;

    std::string_view help_message() const;

    // internal use
    void _call_positional(std::string arg) const;

  private:
    std::bitset<32> _flags;
    std::string _name, _help_msg;
    std::vector<option> _opts;
    std::vector<sub_command> _subcmd;
    std::function<void(const std::string&)> _positional_argument;
};


///
/// \brief parameter subcommand
///
class sub_command : public options_handler {
  public:
    sub_command(std::string subcommand_name, std::function<void(void)> callback, std::string help_msg);

    // internal
    void _call() const;

  private:
    std::function<void(void)> _action;
};


///
/// \brief a given option
///
class option {
  public:
    option(std::string option_name, std::function<void(const std::string&)> callback, std::string help_msg);
    option(std::string option_name, std::function<void(int)> callback, std::string help_msg);
    option(std::string option_name, std::function<void(void)> callback, std::string help_msg);

    std::string_view name() const;

    std::vector<std::string_view> name_and_aliases() const;

    void add_alias(std::string alias);

    bool match(std::string_view opt) const;

    std::string_view help_message() const;


    // internal
    void _call(std::string_view value) const;

    bool _get_flag(int v) const;

  private:
    std::vector<std::string> _names;
    std::string _help_msg;

    std::function<void(const std::string&)> _action;
    std::bitset<32> _flags;
};




void parse_options(const options_handler& opt_handler, int argc, char** argv);

void parse_options(const options_handler& opt_handler, std::string_view prog_name, const std::vector<std::string_view>& options);

} // namespace saxcli
