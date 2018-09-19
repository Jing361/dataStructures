#ifndef __GRAPH_HH__
#define __GRAPH_HH__

#include<utility>
#include<map>
#include<set>

//TODO: consider associating data with edges
//associating data with a node is meaningless for this data structure; this
//  information is more appropriately stored at the client.  However the data of
//  existing edges is intrinsically stored and tracked in this class, and could
//  be useful to obtain.
/*!Type to store/track/interact with graphs.
 *
 * @tparam T data type to track nodes.  This can be an comparable type, but is
 *             preferred to be something that can compare quickly and has small
 *             storage, particularly for larger graphs
 *
 * Stores graphs, and allows for the retrieval of information about the graph,
 * and its nodes/edges.  Can store graphs such as:
 * A-----B
 * |    / \
 * |   /   \
 * |  /    E
 * | /    /
 * |/    /
 * C----D
 * graph<char> g;
 *
 * g.add_node( 'A' );
 * g.emplace_edge( 'B', 'C' );
 * g.add_edge( 'A', 'C' );
 * g.add_edge( 'A', 'B' );
 * g.emplace_edge( 'E', 'E' );
 * g.add_edge( 'C', 'D' );
 * g.add_edge( 'B', 'E' );
 *
 * And information can be retrieved about the graph such as:
 * g.node_count() == 5;
 * g.edge_count() == 6;
 * g.get_nodes() == {'A', 'B', 'C', 'D', 'E'};
 * g.get_edges() == {{'A', 'B'}, {'B', 'A'}, {'A', 'C'}, {'C', 'A'}, etc...};
 * g.adjacent( 'A', 'B' ) == true;
 * g.adjacent( 'A', 'E' ) == false;
 * g.neighbors( 'B' ) == {'A', 'C', 'E'};
 *
 * The graph can also be traversed as:
 * set<node> visited_nodes;
 * set<node> nodes_to_visit = starting_node;
 *
 * while( !nodes_to_visit.empty() ){
 *   auto curr_node = get_next node( nodes_to_visit );
 *   auto neighbors = g.neighbors( curr_node );
 *   nodes_to_visit.insert( purge_visited_nodes( neighbors ) );
 *   visited_nodes.insert( neighbors );
 *
 *   // do something here!
 * }
 */
template<typename T>
class graph{
public:
  using value_type = T;
  using reference = T&;
  using iterator = /**/;
  using edge = std::pair<value_type, value_type>;

private:
  //TODO:investigate multimap?
  std::map<value_type, std::set<value_type> > mNodes;
  //TODO:store a set of all known edges?
  // doing this may assist in removal of edges and nodes.
  // the mNodes map is effectively mOutEdges
  std::map<value_type, std::set<value_type> > mInEdges;

public:
  /*!
   */
  graph() = default;

  /*!
   *
   * @param ref
   */
  void
  add_node( const reference ref ){
    mNodes[ref];
  }

  /*!
   *
   * @param ref
   */
  void
  remove_node( const reference ref ){
    mNodes.erase( mNodes.find( ref ) );

    auto incoming = mInEdges.at( ref );

    for( auto out : outgoing ){
      mInEdges.erase( mInEdges.find( out ) );
    }

    mInEdges.erase( mInEdges.find( ref ) );
  }

  /*!
   *
   * @param refA
   * @param refB
   * @param is_directed
   */
  void
  add_edge( const reference refA, const reference refB, bool is_directed = false ){
    // test for existence of refB
    mNodes.at( refB );

    mNodes.at( refA ).emplace( refB );
    mInEdges[refB] = refA;

    if( !is_directed ){
      mNodes.at( refB ).emplace( refA );
      mInEdges[refA] = refB;
    }
  }

  /*!
   *
   * @param refA
   * @param refB
   */
  void
  remove_edge( const reference refA, const reference refB ){
    auto& edges = mNodes.at( refA );
    edges.erase( edges.find( refB ) );
  }

  /*!
   *
   * @param refA
   * @param refB
   * @param is_directed
   */
  void
  emplace_edge( const reference refA, const reference refB, bool is_directed = false ) {
    mNodes[refA].emplace( refB );
    mInEdges[refB] = refA;

    if( !is_directed ){
      mNodes[refB].emplace( refA );
      mInEdges[refA] = refB;
    }
  }

  /*!
   */
  std::set<value_type>
  get_nodes() const{
    std::set<value_type> result;

    for( auto pr : mNodes ){
      result.emplace( pr.first );
    }

    return result;
  }

  /*!
   */
  std::set<edge>
  get_edges() const{
    std::set<edge> edges;

    for( auto node : mInEdges ){
      for( auto edg : node.second ){
        edges.emplace( node.first, edg );
      }
    }

    for( auto node : mNodes ){
      for( auto edg : node.second ){
        edges.emplace( node.first, edg );
      }
    }

    return result;
  }

  /*!
   *
   * @param ref
   */
  std::set<edge>
  get_edges( const reference ref ) const{
    auto result = get_out_edges( ref );

    auto in = get_in_edges( ref );

    result.insert( in.begin(), in.end() );

    return result;
  }

  /*!
   *
   * @param ref
   */
  std::set<edge>
  get_out_edges( const reference ref ) const{
    return mNodes.at( ref );
  }

  /*!
   *
   * @param ref
   */
  std::set<edge>
  get_in_edges( const reference ref ) const{
    return mInEdges.at( ref );
  }

  /*!
   *
   * @param refA
   * @param refB
   */
  bool
  adjacent( const reference refA, const reference refB ) const{
    //return mNodes.at( refA ).contains( refB );//contains is c++20
    return mNodes.at( refA ).count( refB ) > 0;
  }

  /*!
   *
   * @param ref
   */
  std::set<value_type>
  neighbors( const reference ref ) const{
    return mNodes.at( ref );
  }

  /*!
   */
  size_t
  node_count() const{
    return mNodes.size();
  }

  /*!
   */
  size_t
  edge_count() const{
    unsigned int count = mInEdges.size();

    for( auto pr : mNodes ){
      count += pr.second.size();
    }

    return count;
  }

  /*!
   */
  void
  clear() const{
    mNodes.clear();
    mInEdges.clear();
  }

  /*!
   */
  void
  empty() {
    return mNodes.empty();
  }
};

#endif
