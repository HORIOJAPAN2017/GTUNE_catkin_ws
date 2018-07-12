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

class now_num {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.num_point = null;
      this.last_point = null;
    }
    else {
      if (initObj.hasOwnProperty('num_point')) {
        this.num_point = initObj.num_point
      }
      else {
        this.num_point = 0;
      }
      if (initObj.hasOwnProperty('last_point')) {
        this.last_point = initObj.last_point
      }
      else {
        this.last_point = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type now_num
    // Serialize message field [num_point]
    bufferOffset = _serializer.int16(obj.num_point, buffer, bufferOffset);
    // Serialize message field [last_point]
    bufferOffset = _serializer.int16(obj.last_point, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type now_num
    let len;
    let data = new now_num(null);
    // Deserialize message field [num_point]
    data.num_point = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [last_point]
    data.last_point = _deserializer.int16(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'test_opencv/now_num';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '9cb6f0f19d99868baadd61903a6a1bea';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int16 num_point
    int16 last_point
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new now_num(null);
    if (msg.num_point !== undefined) {
      resolved.num_point = msg.num_point;
    }
    else {
      resolved.num_point = 0
    }

    if (msg.last_point !== undefined) {
      resolved.last_point = msg.last_point;
    }
    else {
      resolved.last_point = 0
    }

    return resolved;
    }
};

module.exports = now_num;
