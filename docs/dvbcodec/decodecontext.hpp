/**
 * Copyright (c) 2004, Thomas Guest. All rights reserved.
 * @file
 * @brief  This file defines the class DecodeContext.
 */

#ifndef DECODECONTEXT_HPP_INCLUDED
#define DECODECONTEXT_HPP_INCLUDED

#include "codectypedefs.hpp"

#include <map>
#include <stack>
#include <string>
#include <iosfwd>

/**
 * @brief Class maintains context during section decoding.
 * 
 * Duties include:
 *   - reading from the (binary) input file, 
 *   - decoding the binary data
 *   - maintaining a record of field values
 */

class DecodeContext
{
public: // construct
    DecodeContext(file_it data_begin,
                  file_it data_end);

public: // read and advance
    /**
     * @brief Read the value of a field
     * @param field_name
     * @param width_of_field_in_bits
     * @returns The value read, as a hex string
     *
     * @note This function is designed to handle arbitrary length 
     * field widths, which is why the result is returned as a string.
     */
    std::string
    readFieldValue(std::string const & field_name,
                   unsigned width_of_field_in_bits);
    

    /**
     * @brief Test if input data has all been processed.
     * @returns True if all data has been processed, false otherwise.
     */
    bool finished() const;
    
public: // conditional and loop support
    
    /**
     * @brief Test a condition
     * @returns The value of expression (field op value)
     * 
     * Example
     *    pushFieldValue("program_number", 0)
     *    testCondition("program_number", "==", 0) --> true
     */
    bool testCondition(std::string const & field,
                       std::string const & op,
                       unsigned long const & value) const;
    
public: // loop support
    /**
     * @brief Register that the current section has a 4 byte CRC.
     *
     * This will affect where the final loop in the section is exited.
     */
    void registerCRC();
    
    /**
     * @brief Section loop exit test.
     * @returns True if the loop has been completed, false
     * otherwise.
     */
    bool testLoopExit();
    
private: // loop support
    void pushLoopExit(unsigned bytes_to_loop_exit);    
    
private: // save values
    void pushFieldValue(std::string const & field,
                        unsigned long const & value);

private: // read and advance
    void getCurrentByte();
    
private:
    unsigned current_byte_; // The current byte from the input stream
    unsigned bits_left_;    // How much of this byte remains to be read
    
    unsigned depth_;        // How deeply nested into the section

    int offset_for_crc_;    // Offset from the end of the section at 
                            // which the last loop ends. Either 4 or 0,
                            // depending on the section type. 
    
    file_it data_begin_;      
    file_it data_end_;
    
    // Record of field values, used in conditional evaluation.
    typedef std::map<std::string, unsigned long> field_values;
    field_values field_values_;
    
    // Stack of file iterators marking loop exits
    std::stack<file_it> loop_exits_;
};

#endif // defined DECODECONTEXT_HPP_INCLUDED
