

function avoidSign(byte)
{
  return (byte & 0b01111111);
}
function getSign(byte)
{
  var mySign = 2;
  if((byte&0b10000000)==1 ) 
  {
    mySign = -1;
  }
  else 
  {
    mySign = 1;
  }
  return mySign;
}

function Decoder(bytes, port) {
    // Decode an uplink message from a buffer
    // (array) of bytes to an object of fields.
    
    ///var i = 0;

// channel, datatype, byte, byte
    var id = ((avoidSign(bytes[0])<<8)|(bytes[1]))*getSign(bytes[0]);
    var a0 = bytes[0];
    var a2 = bytes[0];
    var a3 = bytes[0];
    
    
  //  var longitude = (bytes[i + 5] << 16) | (bytes[i + 6] << 8) | bytes[i + 07];
  //  var altitude = (bytes[i + 8] << 16) | (bytes[i + 9] << 8) | bytes[i + 10];
    
  //  var msb = 0x800000;
  //  if (longitude & msb) longitude -= msb << 1;
  //  if (latitude & msb) latitude -= msb << 1;
   // if (altitude & msb) altitude -= msb << 1;

 /*   var decoded = {
        latitude: latitude / 10000,
        longitude: longitude / 10000,
        altitude: altitude / 100
    };
    */
    var decoded = {
      id : id
    };

    // if (port === 1) decoded.led = bytes[0];

    return decoded;
}








---------------------------------------




function avoidSign(byte)
{
  return (byte & 0b01111111);
}
function getSign(bytee)
{
  var mySign = 2;
  if((bytee&0b10000000)==1 ) 
  {
    mySign = -1;
  }
  else 
  {
    mySign = 1;
  }
  return mySign;
}

function Decoder(bytes, port) {
// channel, datatype, byte, byte
var idSign = bytes[0] & 0b10000000;
    var id = ((bytes[0]-idSign)<<8)|(bytes[1]));
    id = id * idSign;
    var a0 = bytes[0];
    var a2 = bytes[0];
    var a3 = bytes[0];
    
    
  //  var longitude = (bytes[i + 5] << 16) | (bytes[i + 6] << 8) | bytes[i + 07];
  //  var altitude = (bytes[i + 8] << 16) | (bytes[i + 9] << 8) | bytes[i + 10];
    
  //  var msb = 0x800000;
  //  if (longitude & msb) longitude -= msb << 1;
  //  if (latitude & msb) latitude -= msb << 1;
   // if (altitude & msb) altitude -= msb << 1;

 /*   var decoded = {
        latitude: latitude / 10000,
        longitude: longitude / 10000,
        altitude: altitude / 100
    };
    */
    var decoded = {
      id : id
    };

    // if (port === 1) decoded.led = bytes[0];

    return decoded;
}


function twoBytesToDec(byte1, byte2)
{
  var sign = byte1 & 0x80;
}

function Decoder(bytes, port) {
    // Decode an uplink message from a buffer
    // (array) of bytes to an object of fields.
    var i = 4;

    var id = (bytes[2] << 8) | (bytes[3]);
    var a0 = (bytes[6] << 8) | (bytes[7]);
    var a2 = (bytes[10] << 8) | (bytes[11]);
    var a3 = (bytes[14] << 8) | (bytes[15]);
    
    var msb = 0x8000;
    if (id & msb) id -= msb << 1;
    if (a0 & msb) a0 -= msb << 1;
    if (a2 & msb) a2 -= msb << 1;
    if (a3 & msb) a3 -= msb << 1;

    var decoded = {
        id: id / 100,
        a0: a0 / 100,
        a2: a2 / 100,
        a3: a3 / 100
    };

    // if (port === 1) decoded.led = bytes[0];

    return decoded;
}