/*
 * routePlanner.hpp
 *
 *  Created on: Apr 28, 2018
 *      Author: lali
 */


/*
 * This can be solved with other graph implementation but for now I do my own implementation
 * Problem:
 * No endpoint for the route
 * x=>y
 * Decision:
 * The path ignored and dropped from output (all unterminated paths are dropped from the output x=>y rule ignored)
 *
 * Problem:
 * Path contains circle
 * x=>y
 * y=>x
 * Decision:
 * Spanning tree algorithm cuts off the circles
 *
 * Problem:
 * Point is endpoint but also source of route
 * x=>y
 * x=>
 * Decision: x used as endpoint x=>y rule ignored
 *
 *
 * Problem:
 * Two paths leads to the same direction
 * x=>y
 * z=>y
 * z=>
 * Decision:both paths included in the result
 *
 * Problem:
 * Two paths overlaps each other
 * w=>x
 * x=>y
 * y=>z
 * u=>x
 * y=>s
 * s=>
 * z=>
 * Decision:
 * both paths are inluded in the result
 */
#pragma once
#include <string>
#include <deque>
#include <list>
#include <iosfwd>

namespace routePlanner {

/*
 *
 */
class RoutePlanner {
public:
    RoutePlanner();

    /**
     * @brief adds a new waypoint (X=>Y rule)
     * @param locationNameBegin Starting point
     * @param locationNameEnd End point
     */
    void addPoint(const std::string& locationNameBegin, const std::string& locationNameEnd);

    /**
     * @brief Add the Point as endPoint
     * @param locationName Adds a new endpoint (e.g. =>X rule)
     */
    void addEndPoint(const std::string& locationName);

    /**
     * @brief Print the path to the output stream
     * @param outputStream
     */
    void printPath(std::ostream& outputStream) const;

    /**
     * This method should be called when the input ends
     */
    void createSpanningTree();

    virtual ~RoutePlanner();
private:
    struct PathNode
    {
        bool isVisited = false;
        bool isEndpoint = false;
        std::string nodeName;
        PathNode(const std::string& pnodeName, bool pisEndpoint = false ):
            isEndpoint(pisEndpoint), nodeName(pnodeName) {}
    };

    using Path = std::deque<PathNode>;
    using Paths = std::list<Path>;

    Paths paths;


};

} /* namespace routePlanner */
