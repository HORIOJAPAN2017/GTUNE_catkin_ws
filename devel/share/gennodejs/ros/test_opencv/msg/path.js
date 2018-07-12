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

class path {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.gridX = null;
      this.gridY = null;
      this.height = null;
      this.width = null;
      this.theta = null;
      this.number_of_path = null;
    }
    else {
      if (initObj.hasOwnProperty('gridX')) {
        this.gridX = initObj.gridX
      }
      else {
        this.gridX = [];
      }
      if (initObj.hasOwnProperty('gridY')) {
        this.gridY = initObj.gridY
      }
      else {
        this.gridY = [];
      }
      if (initObj.hasOwnProperty('height')) {
        this.height = initObj.height
      }
      else {
        this.height = [];
      }
      if (initObj.hasOwnProperty('width')) {
        this.width = initObj.width
      }
      else {
        this.width = [];
      }
      if (initObj.hasOwnProperty('theta')) {
        this.theta = initObj.theta
      }
      else {
        this.theta = [];
      }
      if (initObj.hasOwnProperty('number_of_path')) {
        this.number_of_path = initObj.number_of_path
      }
      else {
        this.number_of_path = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type path
    // Serialize message field [gridX]
    bufferOffset = _arraySerializer.int16(obj.gridX, buffer, bufferOffset, null);
    // Serialize message field [gridY]
    bufferOffset = _arraySerializer.int16(obj.gridY, buffer, bufferOffset, null);
    // Serialize message field [height]
    bufferOffset = _arraySerializer.int16(obj.height, buffer, bufferOffset, null);
    // Serialize message field [width]
    bufferOffset = _arraySerializer.int16(obj.width, buffer, bufferOffset, null);
    // Serialize message field [theta]
    bufferOffset = _arraySerializer.float32(obj.theta, buffer, bufferOffset, null);
    // Serialize message field [number_of_path]
    bufferOffset = _serializer.int8(obj.number_of_path, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type path
    let len;
    let data = new path(null);
    // Deserialize message field [gridX]
    data.gridX = _arrayDeserializer.int16(buffer, bufferOffset, null)
    // Deserialize message field [gridY]
    data.gridY = _arrayDeserializer.int16(buffer, bufferOffset, null)
    // Deserialize message field [height]
    data.height = _arrayDeserializer.int16(buffer, bufferOffset, null)
    // Deserialize message field [width]
    data.width = _arrayDeserializer.int16(buffer, bufferOffset, null)
    // Deserialize message field [theta]
    data.theta = _arrayDeserializer.float32(buffer, bufferOffset, null)
    // Deserialize message field [number_of_path]
    data.number_of_path = _deserializer.int8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 2 * object.gridX.length;
    length += 2 * object.gridY.length;
    length += 2 * object.height.length;
    length += 2 * object.width.length;
    length += 4 * object.theta.length;
    return length + 21;
  }

  static datatype() {
    // Returns string type for a message object
    return 'test_opencv/path';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'b267f94d1fa74439d6549ff37a25b875';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int16[] gridX
    int16[] gridY
    int16[] height
    int16[] width
    float32[] theta
    int8 number_of_path
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new path(null);
    if (msg.gridX !== undefined) {
      resolved.gridX = msg.gridX;
    }
    else {
      resolved.gridX = []
    }

    if (msg.gridY !== undefined) {
      resolved.gridY = msg.gridY;
    }
    else {
      resolved.gridY = []
    }

    if (msg.height !== undefined) {
      resolved.height = msg.height;
    }
    else {
      resolved.height = []
    }

    if (msg.width !== undefined) {
      resolved.width = msg.width;
    }
    else {
      resolved.width = []
    }

    if (msg.theta !== undefined) {
      resolved.theta = msg.theta;
    }
    else {
      resolved.theta = []
    }

    if (msg.number_of_path !== undefined) {
      resolved.number_of_path = msg.number_of_path;
    }
    else {
      resolved.number_of_path = 0
    }

    return resolved;
    }
};

module.exports = path;
