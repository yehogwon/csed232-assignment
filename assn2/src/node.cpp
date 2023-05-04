/*
 * CSED232 ASSN2
 * Author: Yeho Gwon (20220358)
 * Date: 2023/03/05
 * File Name: node.cpp
 */

#include "node.hpp"

Node::Node(Student data, Node *next) : data(data), next(next) { }

bool operator==(const Node &n1, const Node &n2) {
    return n1.data == n2.data; // compare the data of two nodes
}

void swap_node(Node *node1, Node *node2) {
    Student tmp = node1->data; // declare temporary variable and assign the data of node1 to it
    node1->data = node2->data; // assign the data of node2 to node1
    node2->data = tmp; // assign the data of node1 (stored in the temporary variable) to node2
}
