/**
 * Copyright (c) 2004, Thomas Guest. All rights reserved.
 * @file
 * @brief  This file defines the class DecodeOut.
 */

#ifndef DECODEOUT_HPP_INCLUDED
#define DECODEOUT_HPP_INCLUDED

#include <ostream>
#include <string>

class DecodeContext;

/**
 * @brief Class used for plain text output of decoded sections.
 * 
 * The (generated) section decoder drives the section decoding
 * by calling the functions provided by this class.
 */
class DecodeOut
{
public: // construct
    /**
     * @brief Constructor
     * @param output_stream
     * @param decode_context
     */
    DecodeOut(std::ostream & output_stream,
              DecodeContext & decode_context);

public: // Section decode support

    /**
     * @brief Output a section name.
     * @param section_name
     */
    void
    putSectionName(std::string const & section_name) const;
    
    /**
     * @brief Output a field within the section.
     * @param field_name
     * @param width_of_field_in_bits
     */
    void
    putField(std::string const & field_name,
                unsigned width_of_field_in_bits) const;
    
public: // Control
    
    /**
     * @brief Output the loop control.
     * @param loop_control A string of the form "for(i=0;i<N;i++)"
     */
    void
    putLoopControl(std::string const & loop_control) const;
    
    /**
     * @brief Return true when a loop within the section should exit.
     */
    bool
    testLoopExit() const;
    
    /**
     * @brief Output an "if" conditional.
     * @param field_name
     * @param operation For example, "==".
     * @param value
     * @returns The boolean result of evaluating the condition.
     */
    bool
    putIf(std::string const & field_name,
          std::string const & operation,
          unsigned long const & value) const;
    
    /**
     * @brief Output an "else" conditional.
     * @returns true
     */
    bool
    putElse();
    
public: // Nesting
    /**
     * @brief Enter a nested block in the section.
     */
    void
    enterBlock();
    
    /**
     * @brief Leave a nested block in the section.
     */
    void
    leaveBlock();
    
private:
    std::string indent() const;
    
private:
    std::ostream & out_;
    DecodeContext & context_;
    unsigned depth_;
};

#endif // defined DECODEOUT_HPP_INCLUDED

