#ifndef SWITCH_COMPAT_H
#define SWITCH_COMPAT_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/utime.h>
#include <sys/mkdev.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SOL_TCP IPPROTO_TCP

// todo: libnfs should offer an api to set/override these.
#define getuid() (1000)
#define getgid() (1000)

struct iovec {
  void  *iov_base;
  size_t iov_len;
};

ssize_t writev(int fd, const struct iovec *iov, int iovcnt);
ssize_t readv(int fd, const struct iovec *iov, int iovcnt);

#endif
