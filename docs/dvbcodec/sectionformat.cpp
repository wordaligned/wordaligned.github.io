/**
 * Copyright (c) 2004, Thomas Guest. All rights reserved.
 * @file
 * @brief  This file contains the implementation of various functions 
 * to query the section formats database.
 */

#include "SectionFormat.hpp"

#include <cstring>

namespace
{

/**
 * ETSI EN 300 468 V1.4.1 (2000-11) 15
 * Table 2: Allocation of table_id values
 *
 * Value  Description
 * ------------------
 * 0x00 program_association_section
 * 0x01 conditional_access_section
 * 0x02 program_map_section
 * 0x03 transport_stream_description_section
 * 0x04 to 0x3F reserved
 * 0x40 network_information_section - actual_network
 * 0x41 network_information_section - other_network
 * 0x42 service_description_section - actual_transport_stream
 * 0x43 to 0x45 reserved for future use
 * 0x46 service_description_section - other_transport_stream
 * 0x47 to 0x49 reserved for future use
 * 0x4A bouquet_association_section
 * 0x4B to 0x4D reserved for future use
 * 0x4E event_information_section - actual_transport_stream, present/following
 * 0x4F event_information_section - other_transport_stream, present/following
 * 0x50 to 0x5F event_information_section - actual_transport_stream, schedule
 * 0x60 to 0x6F event_information_section - other_transport_stream, schedule
 * 0x70 time_date_section
 * 0x71 running_status_section
 * 0x72 stuffing_section
 * 0x73 time_offset_section
 * 0x74 to 0x7D reserved for future use
 * 0x7E discontinuity_information_section
 * 0x7F selection_information_section
 * 0x80 to 0xFE user defined
 * 0xFF reserved
 */

static const struct
{
    unsigned char table_id_begin;
    char const * section_name;
}
section_names[] =
    {
        // This table must be kept in order.
        // The section names used for the sections must be the same as
        // those in the section formats array.
        
        { 0x00, "program_association_section" },
        { 0x01, "conditional_access_section" },
        { 0x02, "program_map_section" },
        { 0x03, "transport_stream_description_section" },
        { 0x04, "reserved" },
        { 0x40, "network_information_section" },
        { 0x41, "network_information_section" },
        { 0x42, "service_description_section" },
        { 0x43, "reserved" },
        { 0x46, "service_description_section" },
        { 0x47, "reserved for future use" },
        { 0x4A, "bouquet_association_section" },
        { 0x4B, "reserved for future use" },
        { 0x4E, "event_information_section" },
        { 0x4F, "event_information_section" },
        { 0x50, "event_information_section" },
        { 0x60, "event_information_section" },
        { 0x70, "time_date_section" },
        { 0x71, "running_status_section" },
        { 0x72, "stuffing_section" },
        { 0x73, "time_offset_section" },
        { 0x74, "reserved" },
        { 0x7E, "discontinuity_information_section" },
        { 0x7F, "selection_information_section" },
        { 0x80, "user defined" },
        { 0xFF, "reserved" },
    };

static unsigned const section_name_count =
    sizeof(section_names) / sizeof(section_names[0]);


static const struct
{
    char const * name;
    char const * format;
}
section_formats[] =
    {
        // A descriptor is not really a section.
        // We include it here for convenience.
        {
            "descriptor"
            ,
            " descriptor() {              "
            "     descriptor_tag         8"
            "     descriptor_length      8"
            "     for (i=0; i<N; i++) {   "
            "          private_data_byte 8"
            "     }                       "
            " }                           "
        }
        ,
        // IS0/IEC 13818-1
        // Table 2-26 -- Program association section
        {
            "program_association_section"
            ,
            " program_association_section() {"
            "    table_id                   8"
            "    section_syntax_indicator   1"
            "    '0'                        1"
            "    reserved                   2"
            "    section_length            12"
            "    transport_stream_id       16"
            "    reserved                   2"
            "    version_number             5"
            "    current_next_indicator     1"
            "    section_number             8"
            "    last_section_number        8"
            "    for (i=0; i<N; i++) {       "
            "        program_number        16"
            "        reserved               3"
            "        if(program_number == '0') {"
            "            network_PID       13"
            "        }                       "
            "        else {                  "
            "            program_map_PID   13"
            "        }                       "
            "    }                           "
            "    CRC_32                    32"
            " }                              "
        }
        ,
        {
            // Table 2-28 -- Conditional access section
            "conditional_access_section"
            ,
            "conditional_access_section() {"
            "    table_id                 8"
            "    section_syntax_indicator 1"
            "    '0'                      1"
            "    reserved                 2"
            "    section_length          12"
            "    reserved                18"
            "    version_number           5"
            "    current_next_indicator   1"
            "    section_number           8"
            "    last_section_number      8"
            "    for (i=0; i<N; i++) {     "
            "        descriptor()          "
            "    }                         "
            "    CRC_32                  32"
            "}"
        }
        ,
        {
            // Table 2-29 -- Transport Stream program map section
            "program_map_section"
            ,
            "program_map_section() {                "
            "     table_id                        8 "
            "     section_syntax_indicator        1 "
            "     '0'                             1 "
            "     reserved                        2 "
            "     section_length                 12 "
            "     program_number                 16 " 
            "     reserved                        2 "  
            "     version_number                  5 " 
            "     current_next_indicator          1 "  
            "     section_number                  8 " 
            "     last_section_number             8 " 
            "     reserved                        3 "  
            "     PCR_PID                        13 " 
            "     reserved                        4 "  
            "     program_info_length            12 " 
            "     for (i=0; i<N; i++) {             "
            "         descriptor()                  "
            "     }                                 "
            "     for (i=0;i<N1;i++) {              "
            "         stream_type                 8 " 
            "         reserved                    3 "  
            "         elementary_PID             13 " 
            "         reserved                    4 "  
            "         ES_info_length             12 " 
            "         for (i=0; i<N2; i++) {        "
            "             descriptor()              "
            "         }                             "
            "     }                                 "
            "    CRC_32 32                          "
            " }                                     "
        }
        ,
        {
            // Table 3: Network information section
            // Syntax No. of bits Identifier
            "network_information_section"
            ,
            "network_information_section(){         "
            "    table_id                          8"
            "    section_syntax_indicator          1"
            "    reserved_future_use               1"
            "    reserved                          2"
            "    section_length                   12"
            "    network_id                       16"
            "    reserved                          2"
            "    version_number                    5"
            "    current_next_indicator            1"
            "    section_number                    8"
            "    last_section_number               8"
            "    reserved_future_use               4"
            "    network_descriptors_length       12"
            "    for(i=0;i<N;i++){                  "
            "        descriptor()                   "
            "    }                                  "
            "    reserved_future_use               4"
            "    transport_stream_loop_length     12"
            "    for(i=0;i<N;i++){                  "
            "        transport_stream_id          16"
            "        original_network_id          16"
            "        reserved_future_use           4"
            "        transport_descriptors_length 12"
            "        for(j=0;j<N;j++){              "
            "            descriptor()               "
            "        }                              "
            "    }                                  "
            "    CRC_32 32                          "
            "}                                      "
        }
        ,
        {
            // EN 300 468
            // Table 4: Bouquet association section
            "bouquet_association_section"
            ,
            "bouquet_association_section(){"
            "    table_id 8"
            "    section_syntax_indicator 1"
            "    reserved_future_use 1"
            "    reserved 2"
            "    section_length 12"
            "    bouquet_id 16"
            "    reserved 2"
            "    version_number 5"
            "    current_next_indicator 1"
            "    section_number 8"
            "    last_section_number 8"
            "    reserved_future_use 4"
            "    bouquet_descriptors_length 12"
            "    for(i=0;i<N;i++){"
            "        descriptor()"
            "    }"
            "    reserved_future_use 4"
            "    transport_stream_loop_length 12"
            "    for(i=0;i<N;i++){"
            "        transport_stream_id 16"
            "        original_network_id 16"
            "        reserved_future_use 4"
            "        transport_descriptors_length 12"
            "        for(j=0;j<N;j++){"
            "            descriptor()"
            "        }"
            "    }"
            "    CRC_32 32"
            "}"
        }
        ,
        // EN 300 468
        // Table 5: Service description section
        {
            "service_description_section"
            ,
            "service_description_section(){"
            "    table_id 8"
            "    section_syntax_indicator 1"
            "    reserved_future_use 1"
            "    reserved 2"
            "    section_length 12"
            "    transport_stream_id 16"
            "    reserved 2"
            "    version_number 5"
            "    current_next_indicator 1"
            "    section_number 8"
            "    last_section_number 8"
            "    original_network_id 16"
            "    reserved_future_use 8"
            "    for (i=0;i<N;i++){"
            "        service_id 16"
            "        reserved_future_use 6"
            "        EIT_schedule_flag 1"
            "        EIT_present_following_flag 1"
            "        running_status 3"
            "        free_CA_mode 1"
            "        descriptors_loop_length 12"
            "        for (j=0;j<N;j++){"
            "            descriptor()"
            "        }"
            "    }"
            "    CRC_32 32"
            "}"
        }
        ,
        {
            // EN 300 468
            // Table 7: Event information section
            "event_information_section"
            ,
            "event_information_section(){"
            "    table_id 8"
            "    section_syntax_indicator 1"
            "    reserved_future_use 1"
            "    reserved 2"
            "    section_length 12"
            "    service_id 16"
            "    reserved 2"
            "    version_number 5"
            "    current_next_indicator 1"
            "    section_number 8"
            "    last_section_number 8"
            "    transport_stream_id 16"
            "    original_network_id 16"
            "    segment_last_section_number 8"
            "    last_table_id 8"
            "    for(i=0;i<N;i++){"
            "        event_id 16"
            "        start_time 40"
            "        duration 24"
            "        running_status 3"
            "        free_CA_mode 1"
            "        descriptors_loop_length 12"
            "        for(i=0;i<N;i++){"
            "            descriptor()"
            "        }"
            "    }"
            "    CRC_32 32"
            "}"
        }
        ,
        // EN 300 468
        // Table 8: Time and date section
        {
            "time_date_section"
            ,
            "time_date_section(){"
            "    table_id 8"
            "    section_syntax_indicator 1"
            "    reserved_future_use 1"
            "    reserved 2"
            "    section_length 12"
            "    UTC_time 40"
            "}"
        }
        ,
        {
            //Table 9: Time offset section
            "time_offset_section"
            ,
            "time_offset_section(){"
            "    table_id 8"
            "    section_syntax_indicator 1"
            "    reserved_future_use 1"
            "    reserved 2"
            "    section_length 12"
            "    UTC_time 40"
            "    reserved 4"
            "    descriptors_loop_length 12"
            "    for(i=0;i<N;i++){"
            "        descriptor()"
            "    }"
            "    CRC_32 32"
            "}"
        }
        ,
        {
            // EN 300 468
            // Table 10: Running status section
            "running_status_section"
            ,
            "running_status_section(){"
            "    table_id 8"
            "    section_syntax_indicator 1"
            "    reserved_future_use 1"
            "    reserved 2"
            "    section_length 12"
            "    for (i=0;i<N;i++){"
            "        transport_stream_id 16"
            "        original_network_id 16"
            "        service_id 16"
            "        event_id 16"
            "        reserved_future_use 5"
            "        running_status 3"
            "    }"
            "}"
        }
        ,
        {
            // EN 300 468 Table 11: Stuffing section
            "stuffing_section"
            ,
            "stuffing_section(){"
            "    table_id 8"
            "    section_syntax_indicator 1"
            "    reserved_future_use 1"
            "    reserved 2"
            "    section_length 12"
            "    for (i=0;i<N;i++){"
            "        data_byte 8"
            "    }"
            "}"
        }
    };


static unsigned const format_count =
    sizeof(section_formats) / sizeof(section_formats[0]);


bool inRange(unsigned char i,
             unsigned char begin,
             unsigned char end)
{
    return
        i >= begin && i < end;
}

} // anonymous namespace



char const *
sectionFormat(char const * section_name)
{
    unsigned i = 0;
    
    while (i != format_count &&
           std::strcmp(section_formats[i].name,
                       section_name) != 0)
    {
        ++i;
    }

    return
        i == format_count
        ? 0 : section_formats[i].format;
}


void
getKnownSectionFormats(std::vector<char const *> & formats)
{
    formats.clear();
    formats.reserve(format_count);
    
    for (unsigned i = 0; i != format_count; ++i)
    {
        formats.push_back(section_formats[i].name);
    }
}


char const *
sectionName(unsigned char table_id)
{
    unsigned i = 0;
    
    // The iteration here is a little awkward, since we need to look at two
    // elements of the array at once.    
    while (i != section_name_count - 1)
    {
        if (inRange(table_id,
                    section_names[i].table_id_begin,
                    section_names[i + 1].table_id_begin))
        {
            return section_names[i].section_name;
        }
        ++i;
    }

    return section_names[i].section_name;
}

