/*
 * routePlanner.hpp
 *
 *  Created on: Apr 28, 2018
 *      Author: lali
 */


/*
 * Problem:
 * No endpoint for the route
 * Decision:
 * The path accepted but in the printout marked with an NoEnd at the end
 *
 * Problem:
 * Path contains circle
 * Decision:
 * Path considered faulty
 *
 * Problem:
 * Two paths leads to the same direction
 * Decision:
 * Both paths considered OK
 */
#pragma once
#include <string>
#include <deque>

namespace routePlanner {

/*
 *
 */
class routePlanner {
public:
    routePlanner();

    /**
     * @brief adds a new waypoint
     * @param locationNameBegin
     * @param locationNameEnd
     * @returns true if the addition is possible
     */
    bool addPoint(const std::string& locationNameBegin, const std::string& locationNameEnd);

    /**
     * @brief Mark the Point as endPoint
     * @param locationName
     */
    void markAsEndPoint(const std::string& locationName);

    /**
     * @brief Print the path to the output stream
     * @param outputStream
     */
    void printPath(std::ostream& outputStream);
    virtual ~routePlanner();
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
