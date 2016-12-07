//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_TOPOLOGY_HPP
#define __VIKR_TOPOLOGY_HPP


namespace vikr {


enum Topology {
  VIKR_POINTS,
  VIKR_LINE_STRIP,
  VIKR_LINE_LOOP,
  VIKR_LINES,
  VIKR_TRIANGLE_STRIP,
  VIKR_TRIANGLE_FAN,
  VIKR_TRIANGLES,
  VIKR_TRIANGLE_STRIP_ADJACENCY,
  VIKR_POLYGON,
};
} // vikr
#endif // __VIKR_TOPOLOGY_HPP