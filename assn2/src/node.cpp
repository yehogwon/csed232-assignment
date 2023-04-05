/*
 * CSED232 ASSN2
 * Author: Yeho Gwon (20220358)
 * Date: 2023/03/05
 * File Name: node.hpp
 */

#include "node.hpp"

Node::Node(Student data, Node *next) : data(data), next(next) {}

bool operator==(Node &n1, Node &n2) {
    return n1.data == n2.data;
}

void swap_node(Node *node1, Node *node2) {
    Student tmp = node1->data;
    node1->data = node2->data;
    node2->data = tmp;
}
