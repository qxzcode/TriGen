//
//  mesh_params.h
//  TriGen
//
//  Created by Quinn on 1/31/15.
//
//

#pragma once

#define TARGET_EDGE_LEN 0.5f
#define MIN_EDGE_LEN (TARGET_EDGE_LEN * 4.0f/5.0f)
#define MAX_EDGE_LEN (TARGET_EDGE_LEN * 4.0f/3.0f)

// helper derivatives
#define MAX_EDGE_LEN_SQ (MAX_EDGE_LEN*MAX_EDGE_LEN)
#define MIN_EDGE_LEN_SQ (MIN_EDGE_LEN*MIN_EDGE_LEN)