
import os
import subprocess
import cv2

if __name__ == '__main__':

  xml = '<?xml version="1.0" encoding="UTF-8"?>\
<scene\
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"\
    xsi:noNamespaceSchemaLocation="../../configs/scene.xsd"\
>\
  <height>600</height>\
  <width>600</width>\
  <precision>4</precision>\
  <camera aperture="90">\
    <position x="5" y="0" z="0" />\
    <direction x="-1" y="0" z="0" />\
    <up x="0" y="0" z="1" />\
  </camera>\
  <colors>\
  </colors>\
  <objects>\
    <plane>\
      <translation x="-3" y="0" z="0" />\
      <rotation x="0" y="0" z="0" />\
      <scale x="1" y="1" z="1" />\
      <diffuse />\
      <chessboard color1="air_force_blue_raf" color2="air_force_blue_usaf" />\
    </plane>\
    <box>\
      <translation x="0" y="0" z="0" />\
      <rotation x="0" y="20" z="{}" />\
      <scale x="1" y="1" z="1" />\
      <refractive n="2.4" />\
      <uniform color="red" />\
    </box>\
  </objects>\
</scene>'

  first = True
  os.remove('video.avi')

  for i in range(100):
    print('{} / 100'.format(i))

    with open('image.xml', 'w') as f:
        print(xml.format((i / 100)*90), file=f)

    subprocess.call(['./rt', 'image.xml', 'image.bmp'])

    if first and os.path.isfile('image.bmp'):
      frame = cv2.imread('image.bmp')
      height, width, layers = frame.shape
      video = cv2.VideoWriter('video.avi', 0, 10, (width,height))
      first = False
    elif os.path.isfile('image.bmp'):
      video.write(cv2.imread('image.bmp'))

    try:
      os.remove('image.bmp')
    except:
      print('pass')


  cv2.destroyAllWindows()
  video.release()

  os.remove('image.xml')
