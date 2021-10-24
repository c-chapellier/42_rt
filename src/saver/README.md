# Saver

## PNG file format

The png starts with a header of height bytes signature. It is then composed of chunks containing data.

### Header

The header bytes are in hexadecimal :

```
89 50 4E 47 0D 0A 1A 0A
```

Where :
* 89 : is a transmission byte
* 50 4E 47 : are PNG in ascii
* 0D 0A : A DOS-style line ending (CRLF) to detect DOS-Unix line ending conversion of the data.
* 1A : A byte that stops display of the file under DOS when the command type has been used—the end-of-file character.
* 0A : A Unix-style line ending (LF) to detect Unix-DOS line ending conversion.

### Chunks

All the chunks are composed as follow :

Length | Chunk Type | Chunk Data | CRC
-------|------------|------------|-----
4 bytes | 4 bytes | length bytes | 4 bytes

Where :
* The chunk type is given as 4 ASCII letters. 
<br>The case of the first letter indicates if the chunk is critical or not. Uppercase means critical, lowercase means uncritical.
<br>The case of the second letter indicates if the chunk is public or private. Uppercase means public, lowercase means private.
<br>The case of the third letter must be uppercase. It could be use for future releases.
<br>The case of the fourth letter indicates if the chunk is save to copy.
* The CRC is the 32-CRC of chunk-type and chunk data

The critical chunks are the followings :
* `IHDR`
<br>- It must be the first chunk it contains :
<br>- the image's width (4 bytes)
<br>- the image's height (4 bytes)
<br>- the bit depth (1 byte, values 1, 2, 4, 8, or 16)
<br>- the color type (1 byte, values 0, 2, 3, 4, or 6)
<br>- the compression method (1 byte, value 0)
<br>- the interlace method (1 byte, values 0 "no interlace" or 1 "Adam7 interlace")
* `PLTE`
<br>It contains the palette: a list of colors
* `IDAT`
<br>It contains the image data
* `IEND`
<br>It marks the image end