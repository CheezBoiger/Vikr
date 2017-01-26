//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_TOPOLOGY_HPP
#define __VIKR_TOPOLOGY_HPP


namespace vikr {


/**
  Topology describes how the gpu should draw a given mesh.
  This can stem from Points (or dots that will represent vertex points
  of a mesh), line stips, lines, triangles, and more.
*/
enum Topology {
  VIKR_POINTS,
  VIKR_LINE_STRIP,
  VIKR_LINES,
  VIKR_TRIANGLE_STRIP,
  VIKR_TRIANGLE_FAN,
  VIKR_TRIANGLES,
  VIKR_TRIANGLE_STRIP_ADJACENCY
};
} // vikr
#endif // __VIKR_TOPOLOGY_HPP