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
