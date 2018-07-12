// Auto-generated. Do not edit!

// (in-package test_opencv.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class key {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.ENTER = null;
    }
    else {
      if (initObj.hasOwnProperty('ENTER')) {
        this.ENTER = initObj.ENTER
      }
      else {
        this.ENTER = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type key
    // Serialize message field [ENTER]
    bufferOffset = _serializer.int8(obj.ENTER, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type key
    let len;
    let data = new key(null);
    // Deserialize message field [ENTER]
    data.ENTER = _deserializer.int8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a message object
    return 'test_opencv/key';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'e21e266780e9363474b6e9c1df4da0d9';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int8 ENTER
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new key(null);
    if (msg.ENTER !== undefined) {
      resolved.ENTER = msg.ENTER;
    }
    else {
      resolved.ENTER = 0
    }

    return resolved;
    }
};

module.exports = key;
