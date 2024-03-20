#include <iostream>
#include <unordered_map>

/** @brief Graph namespace */
namespace graph {
    /**
     * @defgroup Exceptions Exceptions
     * @ingroup Exceptions
     *
     * @brief Custom Exceptions class
     *
     * @details
     * A class that handles exceptions in the Graph class.
     */
    class GraphException : public std::exception {
    public:
        GraphException(const char* message) : m_message(message) {}
        const char* what() const noexcept override { return m_message; }
    private:
        const char* m_message;
    };

    /** @defgroup Graph Graph */

    /**
     * @ingroup Graph
     * @brief Graph class
     *
     * @details
     * A class that represents a graph. Contains a map of nodes, each of which contains a map of edges.
     *
     * @tparam key_type - type of the key of the node
     * @tparam value_type - type of the value of the node
     * @tparam weight_type - type of the weight of the edge
     */
    template<typename key_type, typename value_type, typename weight_type>
    class Graph {
    public:
        class Node;

        using const_iterator = typename std::unordered_map<key_type, Node>::const_iterator;
        using iterator = typename std::unordered_map<key_type, Node>::iterator;

        Graph() = default;
        Graph(const Graph& graph) noexcept;
        Graph(Graph&& graph) noexcept;

        Graph& operator=(const Graph& graph) noexcept;
        Graph& operator=(Graph&& graph) noexcept ;

        bool empty() noexcept { return m_umap.empty(); } /**< @brief Checks  if the graph is empty. */
        size_t size() noexcept { return m_umap.size(); } /**< @brief Counts the number of nodes in the graph. */
        void clear() noexcept { return m_umap.clear(); } /**< @brief Removes all nodes from the graph. */

        const_iterator cbegin() const noexcept { return m_umap.cbegin(); }
        const_iterator cend() const noexcept { return m_umap.cend(); }
        iterator begin() noexcept { return m_umap.begin(); }
        iterator end() noexcept { return m_umap.end(); }
        const_iterator begin() const noexcept { return m_umap.cbegin(); }
        const_iterator end() const noexcept { return m_umap.cend(); }

        Node& operator[](const key_type& key) { return m_umap.operator[](key); }
        const Node& operator[](const key_type& key) const { return m_umap.operator[](key); }
        Node& at(const key_type& key);
        const Node& at(const key_type& key) const;

        iterator find(const key_type& key) { return m_umap.find(key); } /**< @brief Finds a node with the given key. */
        const_iterator find(const key_type& key) const { return m_umap.find(key); }

        size_t degree_in(const key_type& key); /**< @brief Counts the number of edges that end in the node with the given key. */
        size_t degree_out(const key_type& key); /**< @brief Counts the number of edges that start in the node with the given key. */
        bool loop(const key_type& key); /**< @brief Checks if the node with the given key has a loop. */


        /** @brief Inserts a node with the given key and value. */
        std::pair<iterator, bool> insert_node(const key_type& key, const value_type& value) { return m_umap.insert({key, Node{value}}); }
        /** @brief Inserts or assigns a node with the given key and value. */
        std::pair<iterator, bool> insert_or_assign_node(key_type key, value_type value) { return m_umap.insert_or_assign(key, Node{value}); }
        /** @brief Inserts an edge. */
        std::pair<typename Node::iterator, bool> insert_edge(std::pair<key_type, key_type> end_points, weight_type weight);
        /** @brief Inserts or assigns an edge. */
        std::pair<typename Node::iterator, bool> insert_or_assign_edge(std::pair<key_type, key_type> end_points, weight_type weight);

        void swap(Graph& graph) noexcept { m_umap.swap(graph.m_umap); } /**< @brief Swaps the contents of the graph. */
    private:
        std::unordered_map<key_type, Node> m_umap; /**< @brief The unordered map that stores the nodes of the graph. */
    };

    /** @brief Swaps the contents of the graph. */
    template<typename key_type, typename value_type, typename weight_type>
    void swap(Graph<key_type, value_type, weight_type> graph1, Graph<key_type, value_type, weight_type> graph2) {
        graph1.swap(graph2);
    }

    /**
     * @ingroup Graph
     * @brief Node class
     *
     * @details Node class is a template class that represents a node in a graph. Uses an unordered map to store the edges.
     *
     * @tparam key_type
     * @tparam value_type
     * @tparam weight_type
     */
    template<typename key_type, typename value_type, typename weight_type>
    class Graph<key_type, value_type, weight_type>::Node {
    public:
        Node() = default;
        explicit Node(value_type value) : m_value(value) {};

        using const_iterator = typename std::unordered_map<key_type, weight_type>::const_iterator;
        using iterator = typename std::unordered_map<key_type, weight_type>::iterator;

        bool empty() noexcept { return m_edge.empty(); } /**< @brief Returns true if the node has no edges, false otherwise. */
        size_t size() noexcept { return m_edge.size(); } /**< @brief Returns the number of edges in the node. */
        value_type& value() noexcept { return m_value; } /**< @brief Returns the value of the node. */
        void clear() noexcept { m_edge.clear(); } /**< @brief Removes all edges from the node. */

        const_iterator cbegin() const noexcept { return m_edge.begin(); }
        const_iterator cend() const noexcept { return m_edge.cend(); }
        iterator begin() noexcept{ return m_edge.begin(); }
        iterator end() noexcept{ return m_edge.end(); }
        const_iterator begin() const noexcept { return m_edge.begin(); }
        const_iterator end() const noexcept { return m_edge.cend(); }

        std::unordered_map<key_type, weight_type> &getedges() noexcept { return m_edge; }
        /** @brief Returns an unordered map of edges */
        const std::unordered_map<key_type, weight_type> &getedges() const noexcept { return m_edge; }
        value_type &getvalue() noexcept { return m_value; } /**< @brief Returns the value of the node. */
        const value_type &getvalue() const noexcept { return m_value; }

        /** @brief Returns the weight of the edge with the given key. */
        std::pair<Node::iterator, bool> insert_edge(key_type key, weight_type weight);
        /** @brief Returns or assigns the weight of the edge with the given key. */
        std::pair<Node::iterator, bool> insert_or_assign_edge(key_type key, weight_type weight);
    private:
        value_type m_value; /**< @brief The value of the node. */
        std::unordered_map<key_type, weight_type> m_edge; /**< @brief The unordered map that stores the edges of the node. */
    };

    template<typename key_type, typename value_type, typename weight_type>
    Graph<key_type, value_type, weight_type>::Graph(const Graph& graph) noexcept {
        m_umap = graph.m_umap;
    }

    template<typename key_type, typename value_type, typename weight_type>
    Graph<key_type, value_type, weight_type>::Graph(Graph<key_type, value_type, weight_type>&& graph) noexcept {
        swap(graph);
    }

    template<typename key_type, typename value_type, typename weight_type>
    Graph<key_type, value_type, weight_type>& Graph<key_type, value_type, weight_type>::operator=(const Graph& graph) noexcept {
        m_umap = graph.m_umap;
        return *this;
    }

    template<typename key_type, typename value_type, typename weight_type>
    Graph<key_type, value_type, weight_type> &Graph<key_type, value_type, weight_type>::operator=(Graph&& graph) noexcept {
        swap(graph);
        return *this;
    }

    template<typename key_type, typename value_type, typename weight_type>
    typename Graph<key_type, value_type, weight_type>::Node& Graph<key_type, value_type, weight_type>::at(const key_type &key) {
        auto find = m_umap.find(key);
        if (find == m_umap.end()) throw GraphException("Key not found");
        return find->second;
    }

    template<typename key_type, typename value_type, typename weight_type>
    const typename Graph<key_type, value_type, weight_type>::Node& Graph<key_type, value_type, weight_type>::at(const key_type& key) const {
        auto find = m_umap.find(key);
        if (find == m_umap.end()) throw GraphException("Key not found");
        return find->second;
    }

    /** @throws If the key is not found, throws GraphException. */
    template<typename key_type, typename value_type, typename weight_type>
    size_t Graph<key_type, value_type, weight_type>::degree_in(const key_type &key) {
        if (m_umap.find(key) == m_umap.end()) throw GraphException("Key not found");
        size_t counter = 0;
        for (auto const &elem: m_umap) {
            auto edges = elem.second.getedges();
            if (edges.find(key) != edges.end()) counter++;
        }
        return counter;
    }

    template<typename key_type, typename value_type, typename weight_type>
    size_t Graph<key_type, value_type, weight_type>::degree_out(const key_type &key) {
        if (m_umap.find(key) == m_umap.end()) throw GraphException("Key not found");
        return (m_umap.find(key))->second.getedges().size();
    }

    template<typename key_type, typename value_type, typename weight_type>
    bool Graph<key_type, value_type, weight_type>::loop(const key_type &key) {
        if (m_umap.find(key) == m_umap.end()) throw GraphException("Key not found");
        auto node_map = m_umap.find(key)->second.getedges();
        if (node_map.find(key) != node_map.end()) return true;
        return false;
    }

    template<typename key_type, typename value_type, typename weight_type>
    std::pair<typename Graph<key_type, value_type, weight_type>::Node::iterator, bool>
    Graph<key_type, value_type, weight_type>::Node::insert_edge(key_type key, weight_type weight) {
        return m_edge.insert({key, weight});
    }

    template<typename key_type, typename value_type, typename weight_type>
    std::pair<typename Graph<key_type, value_type, weight_type>::Node::iterator, bool>
    Graph<key_type, value_type, weight_type>::Node::insert_or_assign_edge(key_type key, weight_type weight) {
        return m_edge.insert_or_assign(key, weight);
    }

    /**
     * @details Inserts an edge between given endpoints with a given value; Uses insert_edge method of Node class
     * @param[in] end_points A pair of two keys
     * @param[in] value The value of the edge
     * @return A pair of a Node::iterator and a bool (success indicator)
     * @throws If the key is not found, throws GraphException.
    */
    template<typename key_type, typename value_type, typename weight_type>
    std::pair<typename Graph<key_type, value_type, weight_type>::Node::iterator, bool>
    Graph<key_type, value_type, weight_type>::insert_edge(std::pair<key_type, key_type> end_points, weight_type weight) {
        auto first = m_umap.find(end_points.first);
        auto second = m_umap.find(end_points.second);
        if (first == m_umap.end()) throw GraphException("Key not found");
        if (second == m_umap.end()) throw GraphException("Key not found");
        return (first->second.insert_edge(end_points.second, weight));
    }

    /**
     * @details Inserts an edge between two nodes or assigns the weight to the edge; Uses insert_or_assign_edge method of Node class.
     * @param[in] end_points A pair of two keys
     * @param[in] value The value of the edge
     * @return A pair of a Node::iterator and a bool (success indicator)
     * @throws If the key is not found, throws GraphException.
    */
    template<typename key_type, typename value_type, typename weight_type>
    std::pair<typename Graph<key_type, value_type, weight_type>::Node::iterator, bool>
    Graph<key_type, value_type, weight_type>::insert_or_assign_edge(std::pair<key_type, key_type> end_points, weight_type weight) {
        if (m_umap.find(end_points.first) == m_umap.end()) throw GraphException("Key not found");
        return (m_umap.find(end_points.first))->second.insert_or_assign_edge(end_points.second, weight);
    }
}