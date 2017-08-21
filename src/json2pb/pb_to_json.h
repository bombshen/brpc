// protobuf-json: Conversions between protobuf and json.
// Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved

// Author: The baidu-rpc authors (pbrpc@baidu.com)
// Date:  2014-10-29 18:30:33

#ifndef BRPC_JSON2PB_PB_TO_JSON_H
#define BRPC_JSON2PB_PB_TO_JSON_H

#include <string>
#include <google/protobuf/message.h>
#include <google/protobuf/io/zero_copy_stream.h> // ZeroCopyOutputStream

namespace json2pb {

enum EnumOption {
    OUTPUT_ENUM_BY_NAME = 0,          // Output enum by its name
    OUTPUT_ENUM_BY_NUMBER = 1,        // Output enum by its value
};

struct Pb2JsonOptions {
    Pb2JsonOptions();

    // Control how enum fields are output
    // Default: OUTPUT_ENUM_BY_NAME
    EnumOption enum_option;

    // Use rapidjson::PrettyWriter to generate the json when this option is on.
    // NOTE: currently PrettyWriter is not optimized yet thus the conversion
    // functions may be slower when this option is turned on.
    bool pretty_json;

    // true, we will automatically convert
    // "repeated { required string key = 1; required string value = 2; }"
    // to a map object of json and vice versa
    bool enable_protobuf_map;
};

// Rules: http://wiki.baidu.com/display/RPC/Json+%3C%3D%3E+Protobuf

// Convert protobuf `messge' to `json' according to `options'.
// Returns true on success. `error' (if not NULL) will be set with error
// message on failure.
bool ProtoMessageToJson(const google::protobuf::Message& message,
                        std::string* json,
                        const Pb2JsonOptions& options,
                        std::string* error = NULL);
// send output to ZeroCopyOutputStream instead of std::string.
bool ProtoMessageToJson(const google::protobuf::Message& message,
                        google::protobuf::io::ZeroCopyOutputStream *json,
                        const Pb2JsonOptions& options,
                        std::string* error = NULL);

// Using default Pb2JsonOptions.
bool ProtoMessageToJson(const google::protobuf::Message& message,
                        std::string* json,
                        std::string* error = NULL);
bool ProtoMessageToJson(const google::protobuf::Message& message,
                        google::protobuf::io::ZeroCopyOutputStream* json,
                        std::string* error = NULL);
} // namespace json2pb

#endif // BRPC_JSON2PB_PB_TO_JSON_H