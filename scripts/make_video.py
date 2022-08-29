
import os
import subprocess
import cv2

if __name__ == '__main__':

  xml = '<?xml version="1.0" encoding="UTF-8"?> \
<scene \
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" \
    xsi:noNamespaceSchemaLocation="scene.xsd" \
> \
  <height>600</height> \
  <width>600</width> \
  <precision>4</precision> \
  <camera aperture="90"> \
    <position x="20" y="0" z="0" /> \
    <direction x="-1" y="0" z="0" /> \
    <up x="0" y="0" z="1" /> \
  </camera> \
  <colors> \
  </colors> \
  <objects> \
    <fresnelsurface> \
      <base> \
        <translation x="0" y="0" z="0" /> \
        <rotation x="0" y="20" z="60" /> \
        <scale x="1" y="1" z="1" /> \
        <diffuse /> \
        <uniform color="red" /> \
      </base> \
      <a>{}</a> \
      <b>{}</b> \
      <c>{}</c> \
    </fresnelsurface> \
  </objects> \
</scene>'

  try:
    os.remove('video.avi')
  except:
    pass

  first = True

  for i in range(4):
    for j in range(4):
      for k in range(4):
        with open('image.xml', 'w') as f:
            print(xml.format(i * 4, j * 4, k * 4), file=f)

        subprocess.call(['./rt', 'image.xml', 'image{}-{}-{}.bmp'.format(i, j, k)])

        if first and os.path.isfile('image{}-{}-{}.bmp'.format(i, j, k)):
          frame = cv2.imread('image{}-{}-{}.bmp'.format(i, j, k))
          height, width, layers = frame.shape
          video = cv2.VideoWriter('video.avi', 0, 10, (width,height))
          first = False
        elif os.path.isfile('image{}-{}-{}.bmp'.format(i, j, k)):
          video.write(cv2.imread('image{}-{}-{}.bmp'.format(i, j, k)))

        # try:
        #   os.remove('image{}-{}-{}.bmp'.format(i, j, k))
        # except:
        #   pass

  cv2.destroyAllWindows()
  video.release()

  os.remove('image.xml')
