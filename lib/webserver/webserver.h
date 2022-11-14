#ifndef __WEBSERVER_H
#define __WEBSERVER_H
#include <Arduino.h>
const char main_HTML[] PROGMEM = "<!doctype html>\n"
"<html lang=\"zh-cmn-Hans\">\n"
"\n"
"<head>\n"
"  <meta charset=\"utf-8\">\n"
"  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1, maximum-scale=1, shrink-to-fit=no\" />\n"
"  <meta name=\"renderer\" content=\"webkit\" />\n"
"  <meta name=\"force-rendering\" content=\"webkit\" />\n"
"  <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge,chrome=1\" />\n"
"\n"
"  <script src=\"https://cdn.bootcdn.net/ajax/libs/three.js/0.146.0/three.min.js\"></script>\n"
"  <link href=\"https://cdn.bootcdn.net/ajax/libs/mdui/1.0.2/css/mdui.min.css\" rel=\"stylesheet\">\n"
"\n"
"  <title>snow ski</title>\n"
"\n"
"\n"
"  <style type=\"text/css\">\n"
"    /*左下角*/\n"
"    div.left_bottom {\n"
"      background: #1a59b7;\n"
"      color: #ffffff;\n"
"      overflow: hidden;\n"
"      z-index: 9999;\n"
"      position: fixed;\n"
"      padding: 5px;\n"
"      text-align: center;\n"
"      width: 175px;\n"
"      height: 300px;\n"
"      border-bottom-left-radius: 4px;\n"
"      border-bottom-right-radius: 4px;\n"
"      border-top-left-radius: 4px;\n"
"      border-top-right-radius: 4px;\n"
"      left: 10px;\n"
"      bottom: 10px;\n"
"    }\n"
"  </style>\n"
"\n"
"</head>\n"
"\n"
"<body>\n"
"  <div class=\"left_bottom\">\n"
"    <p>足部压力传感器</p>\n"
"    <table border=\"1\">\n"
"      <tr>\n"
"        <td id=\"yl-l-1\">0</td>\n"
"        <td id=\"yl-l-2\">0</td>\n"
"        <td id=\"yl-r-1\">0</td>\n"
"        <td id=\"yl-r-2\">0</td>\n"
"      </tr>\n"
"      <tr>\n"
"        <td id=\"yl-l-3\">0</td>\n"
"        <td id=\"yl-l-4\">0</td>\n"
"        <td id=\"yl-r-3\">0</td>\n"
"        <td id=\"yl-r-4\">0</td>\n"
"      </tr>\n"
"      <tr>\n"
"        <td id=\"yl-l-5\">0</td>\n"
"        <td id=\"yl-l-6\">0</td>\n"
"        <td id=\"yl-r-5\">0</td>\n"
"        <td id=\"yl-r-6\">0</td>\n"
"      </tr>\n"
"      <tr>\n"
"        <td id=\"yl-l-7\">0</td>\n"
"        <td id=\"yl-l-8\">0</td>\n"
"        <td id=\"yl-r-7\">0</td>\n"
"        <td id=\"yl-r-8\">0</td>\n"
"      </tr>\n"
"      <tr>\n"
"        <td id=\"yl-l-9\">0</td>\n"
"        <td id=\"yl-l-10\">0</td>\n"
"        <td id=\"yl-r-9\">0</td>\n"
"        <td id=\"yl-r-10\">0</td>\n"
"      </tr>\n"
"      <tr>\n"
"        <td id=\"yl-l-11\">0</td>\n"
"        <td id=\"yl-l-12\">0</td>\n"
"        <td id=\"yl-r-11\">0</td>\n"
"        <td id=\"yl-r-12\">0</td>\n"
"      </tr>\n"
"    </table>\n"
"\n"
"\n"
"  </div>\n"
"  <div class=\"mdui-fab-wrapper\" id=\"fab\">\n"
"    <button class=\"mdui-fab mdui-ripple mdui-color-pink-accent\">\n"
"      <i class=\"mdui-icon material-icons\">add</i>\n"
"      <i class=\"mdui-icon mdui-fab-opened material-icons\">mode_edit</i>\n"
"    </button>\n"
"    <div class=\"mdui-fab-dial\">\n"
"      <button class=\"mdui-fab mdui-fab-mini mdui-ripple mdui-color-pink\" onclick=\"play_it()\">\n"
"        <i class=\"mdui-icon material-icons\">play_arrow</i>\n"
"      </button>\n"
"      <button class=\"mdui-fab mdui-fab-mini mdui-ripple mdui-color-red\">\n"
"        <i class=\"mdui-icon material-icons\">stop</i>\n"
"      </button>\n"
"    </div>\n"
"  </div>\n"
"\n"
"\n"
"  <script>\n"
"\n"
"    mm = { \"t\": [0, 0, 0], \"l\": [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], \"r\": [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0] }\n"
"\n"
"    /**\n"
"     * 创建场景对象Scene\n"
"     */\n"
"    var scene = new THREE.Scene();\n"
"    /**\n"
"     * 创建网格模型\n"
"     */\n"
"    // var geometry = new THREE.SphereGeometry(60, 40, 40); //创建一个球体几何对象\n"
"    var geometry = new THREE.BoxGeometry(60, 10, 100); //创建一个立方体几何对象Geometry\n"
"    var material = new THREE.MeshLambertMaterial({\n"
"      color: 0xf0f0f0\n"
"    }); //材质对象Material\n"
"    var mesh = new THREE.Mesh(geometry, material); //网格模型对象Mesh\n"
"    scene.add(mesh); //网格模型添加到场景中\n"
"\n"
"    var loca_url = \"ws://\" + window.location.host + \"/ws\";\n"
"    // 打开一个 web socket\n"
"    var ws = new WebSocket(loca_url);\n"
"\n"
"    ws.onopen = function () {\n"
"      // Web Socket 已连接上，使用 send() 方法发送数据\n"
"    };\n"
"\n"
"    ws.onmessage = function (evt) {\n"
"      var received_msg = evt.data;\n"
"      try {\n"
"        mm = JSON.parse(received_msg);\n"
"        mesh.rotateX(Math.PI * mm['t'][0]);\n"
"        mesh.rotateY(Math.PI * mm['t'][1]);\n"
"        mesh.rotateZ(Math.PI * mm['t'][2]);\n"
"        document.getElementById(\"yl-l-1\").innerHTML = mm['l'][0];\n"
"        document.getElementById(\"yl-l-2\").innerHTML = mm['l'][1];\n"
"        document.getElementById(\"yl-l-3\").innerHTML = mm['l'][2];\n"
"        document.getElementById(\"yl-l-4\").innerHTML = mm['l'][3];\n"
"        document.getElementById(\"yl-l-5\").innerHTML = mm['l'][4];\n"
"        document.getElementById(\"yl-l-6\").innerHTML = mm['l'][5];\n"
"        document.getElementById(\"yl-l-7\").innerHTML = mm['l'][6];\n"
"        document.getElementById(\"yl-l-8\").innerHTML = mm['l'][7];\n"
"        document.getElementById(\"yl-l-9\").innerHTML = mm['l'][8];\n"
"        document.getElementById(\"yl-l-10\").innerHTML = mm['l'][9];\n"
"        document.getElementById(\"yl-l-11\").innerHTML = mm['l'][10];\n"
"        document.getElementById(\"yl-l-12\").innerHTML = mm['l'][11];\n"
"        document.getElementById(\"yl-r-1\").innerHTML = mm['r'][0];\n"
"        document.getElementById(\"yl-r-2\").innerHTML = mm['r'][1];\n"
"        document.getElementById(\"yl-r-3\").innerHTML = mm['r'][2];\n"
"        document.getElementById(\"yl-r-4\").innerHTML = mm['r'][3];\n"
"        document.getElementById(\"yl-r-5\").innerHTML = mm['r'][4];\n"
"        document.getElementById(\"yl-r-6\").innerHTML = mm['r'][5];\n"
"        document.getElementById(\"yl-r-7\").innerHTML = mm['r'][6];\n"
"        document.getElementById(\"yl-r-8\").innerHTML = mm['r'][7];\n"
"        document.getElementById(\"yl-r-9\").innerHTML = mm['r'][8];\n"
"        document.getElementById(\"yl-r-10\").innerHTML = mm['r'][9];\n"
"        document.getElementById(\"yl-r-11\").innerHTML = mm['r'][10];\n"
"        document.getElementById(\"yl-r-12\").innerHTML = mm['r'][11];\n"
"      }\n"
"      catch (e) {\n"
"        console.err(e);\n"
"        //返回默认对象，或根据用例返回null。\n"
"      }\n"
"    };\n"
"\n"
"    ws.onclose = function () {\n"
"      // 关闭 websocket\n"
"      alert(\"连接已关闭\");\n"
"    }\n"
"\n"
"    /**\n"
"     * 光源设置\n"
"     */\n"
"    //点光源\n"
"    var point = new THREE.PointLight(0xffffff);\n"
"    point.position.set(400, 200, 300); //点光源位置\n"
"    scene.add(point); //点光源添加到场景中\n"
"    //环境光\n"
"    var ambient = new THREE.AmbientLight(0x444444);\n"
"    scene.add(ambient);\n"
"    /**\n"
"     * 相机设置\n"
"     */\n"
"    var width = window.innerWidth; //窗口宽度\n"
"    var height = window.innerHeight; //窗口高度\n"
"    var k = width / height; //窗口宽高比\n"
"    var s = 200; //三维场景显示范围控制系数，系数越大，显示的范围越大\n"
"    //创建相机对象\n"
"    var camera = new THREE.OrthographicCamera(-s * k, s * k, s, -s, 1, 1000);\n"
"    camera.position.set(70, 300, 200); //设置相机位置\n"
"    camera.lookAt(scene.position); //设置相机方向(指向的场景对象)\n"
"    /**\n"
"     * 创建渲染器对象\n"
"     */\n"
"    var renderer = new THREE.WebGLRenderer();\n"
"    renderer.setSize(width, height);//设置渲染区域尺寸\n"
"    renderer.setClearColor(0xb9d3ff, 1); //设置背景颜色\n"
"    document.body.appendChild(renderer.domElement); //body元素中插入canvas对象\n"
"    //执行渲染操作   指定场景、相机作为参数\n"
"    renderer.render(scene, camera);\n"
"\n"
"    function play_it() {\n"
"      document.getElementById(\"yl-r-12\").disabled = true\n"
"    }\n"
"  </script>\n"
"  <script src=\"https://cdn.bootcdn.net/ajax/libs/mdui/1.0.2/js/mdui.min.js\"></script>\n"
"  <script>\n"
"    var $ = mdui.$;\n"
"    var inst = new mdui.Fab('#fab');\n"
"\n"
"    $('#fab').on('open.mdui.fab', function () {\n"
"    });\n"
"\n"
"    $('#fab').on('opened.mdui.fab', function () {\n"
"    });\n"
"\n"
"    $('#fab').on('close.mdui.fab', function () {\n"
"    });\n"
"\n"
"    $('#fab').on('closed.mdui.fab', function () {\n"
"    });\n"
"  </script>\n"
"</body>\n"
"\n"
"</html>";
void int_web();
#endif //__WEBSERVER_H