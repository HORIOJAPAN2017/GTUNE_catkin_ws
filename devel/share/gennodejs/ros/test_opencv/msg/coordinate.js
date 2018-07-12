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

class coordinate {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.gridX = null;
      this.gridY = null;
      this.height = null;
      this.width = null;
      this.theta = null;
    }
    else {
      if (initObj.hasOwnProperty('gridX')) {
        this.gridX = initObj.gridX
      }
      else {
        this.gridX = 0;
      }
      if (initObj.hasOwnProperty('gridY')) {
        this.gridY = initObj.gridY
      }
      else {
        this.gridY = 0;
      }
      if (initObj.hasOwnProperty('height')) {
        this.height = initObj.height
      }
      else {
        this.height = 0;
      }
      if (initObj.hasOwnProperty('width')) {
        this.width = initObj.width
      }
      else {
        this.width = 0;
      }
      if (initObj.hasOwnProperty('theta')) {
        this.theta = initObj.theta
      }
      else {
        this.theta = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type coordinate
    // Serialize message field [gridX]
    bufferOffset = _serializer.int8(obj.gridX, buffer, bufferOffset);
    // Serialize message field [gridY]
    bufferOffset = _serializer.int8(obj.gridY, buffer, bufferOffset);
    // Serialize message field [height]
    bufferOffset = _serializer.int16(obj.height, buffer, bufferOffset);
    // Serialize message field [width]
    bufferOffset = _serializer.int16(obj.width, buffer, bufferOffset);
    // Serialize message field [theta]
    bufferOffset = _serializer.float32(obj.theta, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type coordinate
    let len;
    let data = new coordinate(null);
    // Deserialize message field [gridX]
    data.gridX = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [gridY]
    data.gridY = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [height]
    data.height = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [width]
    data.width = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [theta]
    data.theta = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 10;
  }

  static datatype() {
    // Returns string type for a message object
    return 'test_opencv/coordinate';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'fb7916e2ededf5c749b05192bc80a8dd';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int8 gridX
    int8 gridY
    int16 height
    int16 width
    float32 theta
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new coordinate(null);
    if (msg.gridX !== undefined) {
      resolved.gridX = msg.gridX;
    }
    else {
      resolved.gridX = 0
    }

    if (msg.gridY !== undefined) {
      resolved.gridY = msg.gridY;
    }
    else {
      resolved.gridY = 0
    }

    if (msg.height !== undefined) {
      resolved.height = msg.height;
    }
    else {
      resolved.height = 0
    }

    if (msg.width !== undefined) {
      resolved.width = msg.width;
    }
    else {
      resolved.width = 0
    }

    if (msg.theta !== undefined) {
      resolved.theta = msg.theta;
    }
    else {
      resolved.theta = 0.0
    }

    return resolved;
    }
};

module.exports = coordinate;
