/*
 * Copyright (c) 2012-2014 The nessDB Project Developers. All rights reserved.
 * Code is licensed with GPL. See COPYING.GPL file.
 *
 */

#ifndef nessDB_STATUS_H_
#define nessDB_STATUS_H_

#include "xmalloc.h"
#include "debug.h"

/*
 * some probes
 */
struct status {
	uint64_t tree_leaf_split_nums;
	uint64_t tree_leaf_put_nums;
	uint64_t tree_leaf_nums;
	uint64_t tree_nonleaf_split_nums;
	uint64_t tree_nonleaf_put_nums;
	uint64_t tree_nonleaf_nums;
	uint64_t tree_flush_child_nums;
	uint64_t tree_flush_child_costs;
	uint64_t tree_root_new_nums;
	uint64_t tree_add_pivots_nums;

	uint64_t tree_node_fetch_nums;
	uint64_t tree_node_fetch_costs;
	uint64_t tree_node_flush_nums;
	uint64_t tree_node_flush_costs;

	uint64_t leaf_read_from_disk_nums;
	uint64_t leaf_read_from_disk_costs;
	uint64_t leaf_compress_data_costs;
	uint64_t leaf_uncompress_data_costs;

	uint64_t nonleaf_read_from_disk_nums;
	uint64_t nonleaf_read_from_disk_costs;
	uint64_t nonleaf_compress_data_costs;
	uint64_t nonleaf_uncompress_data_costs;
};

static inline struct status *status_new() {
	struct status *status;

	status = xcalloc(1, sizeof(*status));

	return status;
}

static inline void status_free(struct status *status)
{
#if 1
	__WARN("tree_nodes: leaf [%" PRIu64 "], nonleaf [%" PRIu64 "]",
	       status->tree_leaf_nums,
	       status->tree_nonleaf_nums
	      );

	__WARN("leaf_read_from_disk_nums [%" PRIu64 "]", status->leaf_read_from_disk_nums);
	__WARN("leaf_compress_data_costs [%" PRIu64 "], leaf_uncompress_data_costs [%" PRIu64 "]",
	       status->leaf_compress_data_costs,
	       status->leaf_uncompress_data_costs
	      );

	__WARN("nonleaf_read_from_disk_nums [%" PRIu64 "]", status->nonleaf_read_from_disk_nums);
	__WARN("nonleaf_compress_data_costs [%" PRIu64 "], nonleaf_uncompress_data_costs [%" PRIu64 "]",
	       status->nonleaf_compress_data_costs,
	       status->nonleaf_uncompress_data_costs
	      );

	__WARN("tree_node_fetch_nums [%" PRIu64 "], tree_node_fetch_costs_ms [%" PRIu64 "]",
	       status->tree_node_fetch_nums,
	       status->tree_node_fetch_costs
	      );

	__WARN("tree_flush_child_nums [%" PRIu64 "], tree_flush_child_costs_ms [%" PRIu64 "]",
	       status->tree_flush_child_nums,
	       status->tree_flush_child_costs
	      );

#endif
	xfree(status);
}

#endif /* nessDB_STATUS_H_ */
