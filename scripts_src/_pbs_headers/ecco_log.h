#ifndef ECCO_LOG_H
#define ECCO_LOG_H

#define debug_log(msg)              debug_msg(SCRIPT_REALNAME": "+msg)
#define debug_log_fmt(msg, ...)     debug_msg(SCRIPT_REALNAME": "+string_format(msg, __VA_ARGS__))
#define debug_err(msg)              debug_msg("! ERROR ! "SCRIPT_REALNAME": "+msg)
#define debug_err_fmt(msg, ...)     debug_msg("! ERROR ! "SCRIPT_REALNAME": "+string_format(msg, __VA_ARGS__))

#endif