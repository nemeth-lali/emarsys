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
 * Decision:
 * The path accepted but in the printout marked with an NoEnd at the end
 *
 * Problem:
 * Path contains circle
 * Decision:
 * Spanning tree algorithm cuts off the circles
 *
 * Problem:
 * Two paths leads to the same direction
 * Decision:
 * See above
 */
#pragma once
#include <string>
#include <deque>
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
        bool isEndpoint = false;
        std::string nodeName;
        PathNode(const std::string& pnodeName, bool pisEndpoint = false ):
            isEndpoint(pisEndpoint), nodeName(pnodeName) {}
    };

    using Paths = std::deque<PathNode>;

    Paths paths;
};

} /* namespace routePlanner */
