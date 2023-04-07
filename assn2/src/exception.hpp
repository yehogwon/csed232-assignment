/*
 * CSED232 ASSN2
 * Author: Yeho Gwon (20220358)
 * Date: 2023/03/05
 * File Name: exception.hpp
 */

#ifndef __EXCEPTION_HPP__
#define __EXCEPTION_HPP__

#include <iostream>

// Exception to notice that the user stopped input process to get back to the main menu
class InterruptedInputException : public std::exception { };

#endif