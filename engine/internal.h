/*
 * Copyright (c) 2012-2014 The nessDB Project Developers. All rights reserved.
 * Code is licensed with GPL. See COPYING.GPL file.
 *
 */

#ifndef nessDB_INTERNAL_H_
#define nessDB_INTERNAL_H_

#define _FILE_OFFSET_BITS 64
#ifndef O_BINARY
#define O_BINARY (0)
#endif

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <inttypes.h>
#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include "xmalloc.h"
#include "status.h"
#include "atomic.h"


#define nesslikely(EXPR) __builtin_expect(!! (EXPR), 1)
#define nessunlikely(EXPR) __builtin_expect(!! (EXPR), 0)

/* reserved 1024bytes for double-write tree header */
#define BLOCK_OFFSET_START (ALIGN(1024))

/* reserved NID for block-self using */
#define NID_START (3)
#define FILE_NAME_MAXLEN (256)
#define ZERO_MSN (0)

typedef uint64_t NID;
typedef uint64_t MSN;
typedef uint64_t TXNID;
typedef uint64_t DISKOFF;

/* lock type */
enum lock_type {
	L_NONE = 0,
	L_READ = 1,
	L_WRITE = 2,
};

/* transaction state */
typedef enum txn_state {
	TX_LIVE,
	TX_PREPARING,
	TX_COMMITTING,
	TX_ABORTINT,
} TXNSTATE;

struct txnid_pair {
	TXNID child_xid;
	TXNID parent_xid;
};

#define MSGENTRY_SIZE (sizeof(struct msgentry))
struct msgentry {
	MSN msn;
	uint8_t type;
	struct txnid_pair xidpair;
	uint32_t keylen;
	uint32_t vallen;
} __attribute__((__packed__));

/* key for skiplist */
struct msgarray {
	int size;
	int used;
	int num_cx;
	int num_px;
	struct msgentry **arrays;
};

struct cmp_extra {
	int exists;
};

/*
 * align to ALIGNMENT for direct I/O
 * but it is not always 512 bytes:
 * http://people.redhat.com/msnitzer/docs/io-limits.txt
 */
#define ALIGNMENT (512)
static inline uint64_t ALIGN(uint64_t v)
{
	return (v + ALIGNMENT - 1)&~(ALIGNMENT - 1);
}

#endif /* nessDB_INTERNAL_H_ */
