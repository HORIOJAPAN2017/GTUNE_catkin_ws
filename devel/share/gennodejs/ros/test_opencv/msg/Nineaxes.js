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

class Nineaxes {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.Time = null;
      this.EulerHeading = null;
      this.EulerRoll = null;
      this.AccelerometerX = null;
      this.AccelerometerY = null;
      this.AccelerometerZ = null;
      this.LinearAccelerX = null;
      this.LinearAccelerY = null;
      this.LinearAccelerZ = null;
      this.GravAccelerX = null;
      this.GravAccelerY = null;
      this.GravAccelerZ = null;
      this.EulerPitch = null;
    }
    else {
      if (initObj.hasOwnProperty('Time')) {
        this.Time = initObj.Time
      }
      else {
        this.Time = 0.0;
      }
      if (initObj.hasOwnProperty('EulerHeading')) {
        this.EulerHeading = initObj.EulerHeading
      }
      else {
        this.EulerHeading = 0.0;
      }
      if (initObj.hasOwnProperty('EulerRoll')) {
        this.EulerRoll = initObj.EulerRoll
      }
      else {
        this.EulerRoll = 0.0;
      }
      if (initObj.hasOwnProperty('AccelerometerX')) {
        this.AccelerometerX = initObj.AccelerometerX
      }
      else {
        this.AccelerometerX = 0.0;
      }
      if (initObj.hasOwnProperty('AccelerometerY')) {
        this.AccelerometerY = initObj.AccelerometerY
      }
      else {
        this.AccelerometerY = 0.0;
      }
      if (initObj.hasOwnProperty('AccelerometerZ')) {
        this.AccelerometerZ = initObj.AccelerometerZ
      }
      else {
        this.AccelerometerZ = 0.0;
      }
      if (initObj.hasOwnProperty('LinearAccelerX')) {
        this.LinearAccelerX = initObj.LinearAccelerX
      }
      else {
        this.LinearAccelerX = 0.0;
      }
      if (initObj.hasOwnProperty('LinearAccelerY')) {
        this.LinearAccelerY = initObj.LinearAccelerY
      }
      else {
        this.LinearAccelerY = 0.0;
      }
      if (initObj.hasOwnProperty('LinearAccelerZ')) {
        this.LinearAccelerZ = initObj.LinearAccelerZ
      }
      else {
        this.LinearAccelerZ = 0.0;
      }
      if (initObj.hasOwnProperty('GravAccelerX')) {
        this.GravAccelerX = initObj.GravAccelerX
      }
      else {
        this.GravAccelerX = 0.0;
      }
      if (initObj.hasOwnProperty('GravAccelerY')) {
        this.GravAccelerY = initObj.GravAccelerY
      }
      else {
        this.GravAccelerY = 0.0;
      }
      if (initObj.hasOwnProperty('GravAccelerZ')) {
        this.GravAccelerZ = initObj.GravAccelerZ
      }
      else {
        this.GravAccelerZ = 0.0;
      }
      if (initObj.hasOwnProperty('EulerPitch')) {
        this.EulerPitch = initObj.EulerPitch
      }
      else {
        this.EulerPitch = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Nineaxes
    // Serialize message field [Time]
    bufferOffset = _serializer.float32(obj.Time, buffer, bufferOffset);
    // Serialize message field [EulerHeading]
    bufferOffset = _serializer.float32(obj.EulerHeading, buffer, bufferOffset);
    // Serialize message field [EulerRoll]
    bufferOffset = _serializer.float32(obj.EulerRoll, buffer, bufferOffset);
    // Serialize message field [AccelerometerX]
    bufferOffset = _serializer.float32(obj.AccelerometerX, buffer, bufferOffset);
    // Serialize message field [AccelerometerY]
    bufferOffset = _serializer.float32(obj.AccelerometerY, buffer, bufferOffset);
    // Serialize message field [AccelerometerZ]
    bufferOffset = _serializer.float32(obj.AccelerometerZ, buffer, bufferOffset);
    // Serialize message field [LinearAccelerX]
    bufferOffset = _serializer.float32(obj.LinearAccelerX, buffer, bufferOffset);
    // Serialize message field [LinearAccelerY]
    bufferOffset = _serializer.float32(obj.LinearAccelerY, buffer, bufferOffset);
    // Serialize message field [LinearAccelerZ]
    bufferOffset = _serializer.float32(obj.LinearAccelerZ, buffer, bufferOffset);
    // Serialize message field [GravAccelerX]
    bufferOffset = _serializer.float32(obj.GravAccelerX, buffer, bufferOffset);
    // Serialize message field [GravAccelerY]
    bufferOffset = _serializer.float32(obj.GravAccelerY, buffer, bufferOffset);
    // Serialize message field [GravAccelerZ]
    bufferOffset = _serializer.float32(obj.GravAccelerZ, buffer, bufferOffset);
    // Serialize message field [EulerPitch]
    bufferOffset = _serializer.float32(obj.EulerPitch, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Nineaxes
    let len;
    let data = new Nineaxes(null);
    // Deserialize message field [Time]
    data.Time = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [EulerHeading]
    data.EulerHeading = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [EulerRoll]
    data.EulerRoll = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [AccelerometerX]
    data.AccelerometerX = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [AccelerometerY]
    data.AccelerometerY = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [AccelerometerZ]
    data.AccelerometerZ = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [LinearAccelerX]
    data.LinearAccelerX = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [LinearAccelerY]
    data.LinearAccelerY = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [LinearAccelerZ]
    data.LinearAccelerZ = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [GravAccelerX]
    data.GravAccelerX = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [GravAccelerY]
    data.GravAccelerY = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [GravAccelerZ]
    data.GravAccelerZ = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [EulerPitch]
    data.EulerPitch = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 52;
  }

  static datatype() {
    // Returns string type for a message object
    return 'test_opencv/Nineaxes';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '2fcf5021dd14ec1f7c21636820e9d8c9';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 Time
    float32 EulerHeading
    float32 EulerRoll
    float32 AccelerometerX
    float32 AccelerometerY
    float32 AccelerometerZ
    float32 LinearAccelerX
    float32 LinearAccelerY
    float32 LinearAccelerZ
    float32 GravAccelerX
    float32 GravAccelerY
    float32 GravAccelerZ
    float32 EulerPitch
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Nineaxes(null);
    if (msg.Time !== undefined) {
      resolved.Time = msg.Time;
    }
    else {
      resolved.Time = 0.0
    }

    if (msg.EulerHeading !== undefined) {
      resolved.EulerHeading = msg.EulerHeading;
    }
    else {
      resolved.EulerHeading = 0.0
    }

    if (msg.EulerRoll !== undefined) {
      resolved.EulerRoll = msg.EulerRoll;
    }
    else {
      resolved.EulerRoll = 0.0
    }

    if (msg.AccelerometerX !== undefined) {
      resolved.AccelerometerX = msg.AccelerometerX;
    }
    else {
      resolved.AccelerometerX = 0.0
    }

    if (msg.AccelerometerY !== undefined) {
      resolved.AccelerometerY = msg.AccelerometerY;
    }
    else {
      resolved.AccelerometerY = 0.0
    }

    if (msg.AccelerometerZ !== undefined) {
      resolved.AccelerometerZ = msg.AccelerometerZ;
    }
    else {
      resolved.AccelerometerZ = 0.0
    }

    if (msg.LinearAccelerX !== undefined) {
      resolved.LinearAccelerX = msg.LinearAccelerX;
    }
    else {
      resolved.LinearAccelerX = 0.0
    }

    if (msg.LinearAccelerY !== undefined) {
      resolved.LinearAccelerY = msg.LinearAccelerY;
    }
    else {
      resolved.LinearAccelerY = 0.0
    }

    if (msg.LinearAccelerZ !== undefined) {
      resolved.LinearAccelerZ = msg.LinearAccelerZ;
    }
    else {
      resolved.LinearAccelerZ = 0.0
    }

    if (msg.GravAccelerX !== undefined) {
      resolved.GravAccelerX = msg.GravAccelerX;
    }
    else {
      resolved.GravAccelerX = 0.0
    }

    if (msg.GravAccelerY !== undefined) {
      resolved.GravAccelerY = msg.GravAccelerY;
    }
    else {
      resolved.GravAccelerY = 0.0
    }

    if (msg.GravAccelerZ !== undefined) {
      resolved.GravAccelerZ = msg.GravAccelerZ;
    }
    else {
      resolved.GravAccelerZ = 0.0
    }

    if (msg.EulerPitch !== undefined) {
      resolved.EulerPitch = msg.EulerPitch;
    }
    else {
      resolved.EulerPitch = 0.0
    }

    return resolved;
    }
};

module.exports = Nineaxes;
