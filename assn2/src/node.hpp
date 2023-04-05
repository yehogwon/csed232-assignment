/*
 * CSED232 ASSN2
 * Author: Yeho Gwon (20220358)
 * Date: 2023/03/05
 * File Name: node.hpp
 */

#ifndef __NODE_HPP__
#define __NODE_HPP__

#include "student.hpp"

class Node {
public: 
    Student data; // data
    Node *next; // pointer to next node

    /**
     * @brief constructor of Node
     * @param data data of student type to store in this node
     * @param next pointer to next node 
     */
    // TODO: what about use default argument for next?
    Node(Student data, Node *next);
};

/**
 * @brief Compare two nodes
 * @param n1 operand 1
 * @param n2 operand 2
 * @return true if n1 == n2, false otherwise
 */
bool operator==(const Node &n1, const Node &n2);

/**
 * @brief Swap two nodes
 * @param node1 operand 1
 * @param node2 operand 2
 * @return none
 */
void swap_node(Node *node1, Node *node2);

#endif