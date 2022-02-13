import React from 'react';
import axios from 'axios';
import logo from './logo.svg';
import './App.css';

interface Response {
  statusCode: number,
  message: string
}

const App = () => {

  const [img, setImg] = React.useState<string>("iVBORw0KGgoAAAANSUhEUgAAADMAAAAzCAYAAAA6oTAqAAAAEXRFWHRTb2Z0d2FyZQBwbmdjcnVzaEB1SfMAAABQSURBVGje7dSxCQBACARB+2/ab8BEeQNhFi6WSYzYLYudDQYGBgYGBgYGBgYGBgYGBgZmcvDqYGBgmhivGQYGBgYGBgYGBgYGBgYGBgbmQw+P/eMrC5UTVAAAAABJRU5ErkJggg==");

  const scene = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><scene    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">  <height>600</height>  <width>600</width>  <precision>4</precision>  <camera aperture=\"90\">    <position x=\"5\" y=\"0\" z=\"0\" />    <direction x=\"-1\" y=\"0\" z=\"0\" />    <up x=\"0\" y=\"0\" z=\"1\" />  </camera>  <colors>  </colors>  <objects>    <sphere>      <translation x=\"0\" y=\"0\" z=\"0\" />      <rotation x=\"0\" y=\"0\" z=\"0\" />      <scale x=\"1\" y=\"1\" z=\"1\" />      <diffuse />      <uniform color=\"red\" />    </sphere>  </objects></scene>"
  
  React.useEffect(() => {

    const getImg = async () => {
      try {
        const res = await axios.post(
          `http://localhost:8000`,
          scene
        );
        const data: Response = res.data;
        // console.log(data.message);
        setImg(data.message);
      } catch (error) {
        console.error(error);
      }
    }

    getImg();

  })

  return (
    <div className="App">
      <header className="App-header">
        <img
          // style={{ width: 66, height: 58 }}
          alt="raytraced"
          src={"data:image/png;base64," + img}
        />
      </header>
    </div>
  );
}

export default App;
