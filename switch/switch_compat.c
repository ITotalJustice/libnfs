#include "switch_compat.h"

#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#if 0
ssize_t writev(int fd, const struct iovec *iov, int iovcnt) {
    ssize_t total = 0;
    for (int i = 0; i < iovcnt; ++i) {
        size_t to_write = iov[i].iov_len;
        char *base = (char *)iov[i].iov_base;

        while (to_write > 0) {
            ssize_t written = write(fd, base, to_write);
            if (written < 0) {
                return (total > 0) ? total : -1;
            }

            if (written == 0) {
                // Should not happen, but avoid infinite loop
                break;
            }

            total += written;
            to_write -= written;
            base += written;
        }

        if (to_write > 0) {
            // Partial write, stop as per POSIX
            break;
        }
    }
    return total;
}


ssize_t readv(int fd, const struct iovec *iov, int iovcnt) {
    ssize_t total = 0;
    for (int i = 0; i < iovcnt; ++i) {
        size_t to_read = iov[i].iov_len;
        char *base = (char *)iov[i].iov_base;

        while (to_read > 0) {
            ssize_t nread = read(fd, base, to_read);
            if (nread < 0) {
                return (total > 0) ? total : -1;
            }

            if (nread == 0) {
                // EOF
                return total;
            }

            total += nread;
            to_read -= nread;
            base += nread;
        }

        if (to_read > 0) {
            // Partial read, stop as per POSIX
            break;
        }
    }

    return total;
}
#endif
