#ifndef PICL_OPTIMIZE_H
# define PICL_OPTIMIZE_H
# include "picl-object.h"
# include "picl-node.h"
# include "picl-optimize-env.h"

/*
 *   変数名 
 */

void Picl_optimize_nodes(struct PiclNodeArray *nodes, struct PiclOptimizeEnv *optimize_env);

#endif /* PICL_OPTIMIZE_H */
