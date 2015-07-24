/*
 * Copyright (c) 2015, Gary Guo 
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met: 
 * 
 *  * Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer. 
 *  * Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND ANY 
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR ANY 
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY 
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
 * DAMAGE. 
 */

#include <string.h>
#include <errno.h>

char *strerror_l(int errnum, locale_t locale) {
	switch (errnum) {
		case 0				: return "No error information";
		case E2BIG          : return "Argument list too long";
		case EACCES         : return "Permission denied";
		case EADDRINUSE     : return "Address in use";
		case EADDRNOTAVAIL  : return "Address not available";
		case EAFNOSUPPORT   : return "Address family not supported by protocol";
		case EAGAIN         : return "Resource temporarily unavailable";
		case EALREADY       : return "Operation already in progress";
		case EBADF          : return "Bad file descriptor";
		case EBADMSG        : return "Bad message";
		case EBUSY          : return "Resource busy";
		case ECANCELED      : return "Operation canceled";
		case ECHILD         : return "No child process";
		case ECONNABORTED   : return "Connection aborted";
		case ECONNREFUSED   : return "Connection refused";
		case ECONNRESET     : return "Connection reset by peer";
		case EDEADLK        : return "Resource deadlock would occur";
		case EDESTADDRREQ   : return "Destination address required";
		case EDOM           : return "Domain error";
		case EDQUOT         : return "Quota exceeded";
		case EEXIST         : return "File exists";
		case EFAULT         : return "Bad address";
		case EFBIG          : return "File too large";
		case EHOSTUNREACH   : return "Host is unreachable";
		case EIDRM          : return "Identifier removed";
		case EILSEQ         : return "Illegal byte sequence";
		case EINPROGRESS    : return "Operation in progress";
		case EINTR          : return "Interrupted system call";
		case EINVAL         : return "Invalid argument";
		case EIO            : return "I/O error";
		case EISCONN        : return "Socket is connected";
		case EISDIR         : return "Is a directory";
		case ELOOP          : return "Symbolic link loop";
		case EMFILE         : return "No file descriptors available";
		case EMLINK         : return "Too many links";
		case EMSGSIZE       : return "Message too large";
		case EMULTIHOP      : return "Reserved";
		case ENAMETOOLONG   : return "Filename too long";
		case ENETDOWN       : return "Network is down";
		case ENETRESET      : return "Connection reset by network";
		case ENETUNREACH    : return "Network unreachable";
		case ENFILE         : return "Too many open files in system";
		case ENOBUFS        : return "No buffer space available";
		case ENODATA        : return "No data available";
		case ENODEV         : return "No such device";
		case ENOENT         : return "No such file or directory";
		case ENOEXEC        : return "Exec format error";
		case ENOLCK         : return "No locks available";
		case ENOLINK        : return "Link has been severed";
		case ENOMEM         : return "Out of memory";
		case ENOMSG         : return "No message of desired type";
		case ENOPROTOOPT    : return "Protocol not available";
		case ENOSPC         : return "No space left on device";
		case ENOSR          : return "Out of streams resources";
		case ENOSTR         : return "Device not a stream";
		case ENOSYS         : return "Function not implemented";
		case ENOTCONN       : return "Socket not connected";
		case ENOTDIR        : return "Not a directory";
		case ENOTEMPTY      : return "Directory not empty";
		case ENOTRECOVERABLE: return "State not recoverable";
		case ENOTSOCK       : return "Not a socket";
		case ENOTSUP        : return "Not supported";
		case ENOTTY         : return "Not a tty";
		case ENXIO          : return "No such device or address";
		case EOVERFLOW      : return "Value too large for data type";
		case EOWNERDEAD     : return "Previous owner died";
		case EPERM          : return "Operation not permitted";
		case EPIPE          : return "Broken pipe";
		case EPROTO         : return "Protocol error";
		case EPROTONOSUPPORT: return "Protocol not supported";
		case EPROTOTYPE     : return "Protocol wrong type for socket";
		case ERANGE         : return "Result not representable";
		case EROFS          : return "Read-only file system";
		case ESPIPE         : return "Invalid seek";
		case ESRCH          : return "No such process";
		case ESTALE         : return "Stale file handle";
		case ETIME          : return "Device timeout";
		case ETIMEDOUT      : return "Operation timed out";
		case ETXTBSY        : return "Text file busy";
		case EXDEV          : return "Cross-device link";
		default				: errno = EINVAL; return "Unknown error";
	}
}