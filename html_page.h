char html_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="pt-br">
    <head>
        <meta charset="utf-8" />
        <meta name="viewport" content="width=device-width, user-scalable=no" />
        <style type="text/css">
            .button {
                background-color: Gray;
                border: none;
                color: #fff;
                padding: 15px 32px;
                text-align: center;
                text-decoration: none;
                display: inline-block;
                font-size: 16px;
                margin: 4px 2px;
                cursor: pointer;
            }
            .switch {
                font: normal normal 1em sans-serif;
                cursor: pointer;
                display: inline-block;
                position: relative;
                vertical-align: middle;
                text-align: left;
                overflow: hidden;
                width: 4.5em;
                height: 2em;
                border-radius: 2em;
                transition: background 0.2s, text-indent 0.2s;
                background: #ee2929;
                border: 1px solid #666;
                box-shadow: inset 0 0 0.5em;
            }
            .switch-on,
            input:checked + .switch {
                background: #090;
                text-indent: 2.5em;
                animation: colorize 10s linear infinite;
            }
            .switch:before {
                content: "ON OFF";
                word-spacing: 2.3em;
                text-indent: -93%;
                display: inline-block;
                position: relative;
                width: 2em;
                height: 2em;
                line-height: 2em;
                border-radius: 50%;
                white-space: pre;
                transition: box-shadow 0.2s;
                background: #aaa;
                color: #fff;
                text-shadow: 1px -1px 1px rgba(0, 0, 0, 0.3);
                box-shadow: inset 0 0 0.4em #fff, 0.2em 0 0.2em rgba(0, 0, 0, 0.6);
            }
            .switch-on:before,
            input:checked + .switch:before {
                box-shadow: inset 0 0 0.4em #fff, -0.2em 0 0.2em rgba(0, 0, 0, 0.6);
            }
            .divcheckbt {
                flex-direction: row;
            }
            @media (orientation: landscape) {
                .checkbt {
                    width: 300px;
                    padding: 10px 25px 10px 25px;
                    display: flex;
                    flex-direction: row;
                    flex-wrap: nowrap;
                    align-content: space-around;
                    justify-content: space-between;
                    align-items: center;
                    font-family: Arial, Times, serif;
                    font-size: 20px;
                }
            }
            @media (orientation: portrait) {
                .checkbt {
                    width: 300px;
                    padding: 2px 25px 2px 25px;
                    display: flex;
                    flex-direction: row;
                    flex-wrap: nowrap;
                    align-content: space-around;
                    justify-content: space-between;
                    align-items: center;
                    font-family: Arial, Times, serif;
                }
            }
            *,
            :after,
            :before {
                box-sizing: border-box;
            }
            .toggle {
                position: relative;
                top: 60%;
                left: 50%;
                transform: translate3d(-50%, -50%, 0);
                display: flex;
                flex-direction: column;
                flex-wrap: nowrap;
                align-content: center;
                justify-content: space-between;
                align-items: center;
                height: 140px;
                font-style: italic;
                font-weight: 700;
                font-size: 18px;
                font-family: arial, sans-serif;
                color: #555;
            }
            .toggle label {
                position: relative;
                display: inline-block;
                width: 80px;
                height: 80px;
                background-color: #fd1015;
                border-radius: 50px;
                cursor: pointer;
                box-shadow: inset 0 0 2px 1px rgba(0, 0, 0, 0.1), 0 9px 15px 0 #ef4247;
                -webkit-tap-highlight-color: transparent;
            }
            .toggle label:before {
                content: "";
                position: absolute;
                top: 50%;
                left: 50%;
                transform: translate(-50%, -50%);
                transition: width 0.2s cubic-bezier(0, -1.85, 0.27, 1.75);
                height: 42px;
                width: 42px;
                background-color: #fd0f14;
                border-radius: 46px;
                box-shadow: inset 0 0 0 8px #fff;
            }
            .toggle input {
                display: none;
            }
            .toggle input:checked + label {
                background-color: #57de72;
                box-shadow: inset 0 0 2px 1px rgba(0, 0, 0, 0.1), 0 9px 15px 0 rgba(3, 132, 28, 0.5411764706);
            }
            .toggle input:checked + label:before {
                width: 10px;
                background-color: #fff;
            }
            .on {
                background-color: #6fc57c;
            }
            .on .toggle:before {
                color: rgba(62, 160, 81, 0.89);
            }
            .on .toggle:after {
                color: #fff;
            }
            .aba_home_e {
                display: flex;
                flex-direction: column;
                align-items: flex-start;
                width: 60vw;
                height: 83vh;
            }
            .aba_home_d {
                width: 40vw;
                height: 83vh;
            }
            .spantimes {
                width: 100px;
                border: 2px solid #555;
                background: #aaa;
                padding: 1vh;
                font-family: Arial, Times, serif;
                font-size: 2vh;
            }
            .vel {
                font-size: 25px;
            }
            .atimes {
                font-size: 42px;
            }
            #vel_maq {
                font-size: 10vh;
                width: auto;
                border: 2px solid #555;
                background: #aaa;
                padding: 1vh;
                font-family: Arial, Times, serif;
            }
            .div_velocidade + a {
                font-family: Arial, Times, serif;
            }
            @media (orientation: landscape) {
                .tec_geral {
                    top: 12.5vh;
                    width: 45vh;
                    height: 75vh;
                    position: absolute;
                    flex-direction: column;
                    opacity: 1;
                    z-index: 1000;
                }
                #campo {
                    height: 9vh;
                    width: 45vh;
                    font: bold 4.5vh "Trebuchet MS", Arial;
                    padding: 0;
                    border: 0;
                    margin: 0;
                }
                #c {
                    height: 9vh;
                    width: 45vh;
                }
                #botoes input {
                    float: left;
                    height: 15vh;
                    width: 15vh;
                    font: bold 7.5vh "Trebuchet MS", Arial;
                }
                #desc_t {
                    height: 6vh;
                    width: 45vh;
                    font: bold 2.5vh "Trebuchet MS", Arial;
                    text-align: center;
                    background: #666;
                    float: left;
                }
            }
            @media (orientation: portrait) {
                .tec_geral {
                    top: 25vh;
                    width: 30vh;
                    height: 50vh;
                    position: absolute;
                    flex-direction: column;
                    opacity: 1;
                    z-index: 1000;
                }
                #campo {
                    height: 6vh;
                    width: 30vh;
                    font: bold 4.5vh "Trebuchet MS", Arial;
                    padding: 0;
                    border: 0;
                    margin: 0;
                }
                #c {
                    height: 6vh;
                    width: 30vh;
                }
                #botoes input {
                    float: left;
                    height: 10vh;
                    width: 10vh;
                    font: bold 5vh "Trebuchet MS", Arial;
                }
                #desc_t {
                    height: 4vh;
                    width: 30vh;
                    font: bold 2.5vh "Trebuchet MS", Arial;
                    text-align: center;
                    background: #666;
                    float: left;
                }
            }
            #tec_geral_d {
                display: none;
            }
            #timers {
                width: 100%;
                height: 85vh;
                position: absolute;
            }
            @media (orientation: landscape) {
                .edit_times {
                    display: inline-block;
                    background: #888;
                    width: 42vw;
                    height: 18vh;
                    margin: 1vh 2vw 1vh 2vw;
                }
                .spantimes {
                    width: 100px;
                    border: 2px solid #555;
                    background: #aaa;
                    padding: 1vw;
                    font-family: Arial, Times, serif;
                    font-size: 2vh;
                }
                .atimes {
                    font-size: 3.5vh;
                    line-height: 2;
                }
            }
            @media (orientation: portrait) {
                .edit_times {
                    display: inline-block;
                    background: #888;
                    width: 84vw;
                    height: 8vh;
                    margin-bottom: 0.4vh;
                    margin-top: 0.4vh;
                    margin-left: 1vw;
                    margin-right: 1vw;
                    border-radius: 4px;
                }
                .spantimes {
                    width: 100px;
                    border: 2px solid #555;
                    background: #aaa;
                    padding: 1vw;
                    font-family: Arial, Times, serif;
                    font-size: 2vh;
                }
                .atimes {
                    font-size: 1.8vh;
                    line-height: 2;
                }
            }
            .class_divgeral_alarme {
                display: flex;
                position: absolute;
                top: 35vh;
                width: 60vh;
                height: 30vh;
                z-index: 1001;
                flex-direction: column;
                align-items: center;
                justify-content: space-around;
                background-color: gray;
            }
            .class_div_alarme {
                font-size: 3.5vh;
                text-transform: uppercase;
                display: flex;
                font-family: Arial, Helvetica, sans-serif;
                color: #fff146;
                background-color: gray;
                justify-content: space-around;
                align-items: center;
                width: -webkit-fill-available;
                height: -webkit-fill-available;
            }
            .button {
                border: none;
                color: #fff;
                padding: 15px 32px;
                text-align: center;
                text-decoration: none;
                display: inline-block;
                font-size: 16px;
                margin: 4px 2px;
                cursor: pointer;
            }
            .green {
                background-color: #4caf50;
            }
            .buttons {
                width: auto;
                heigth: auto;
                padding: 1.5vh;
            }
            .botaoh {
                background-color: #999;
                border: none;
                border-radius: 4vh;
                color: #fff;
                margin-bottom: 1.5vh;
                margin-left: 1.5vh;
                margin-right: 1.5vh;
                margin-top: 1.5vh;
                width: 20vw;
                height: 16vh;
                text-align: center;
                text-decoration: none;
                display: inline-block;
                font-size: 2vw;
                padding: 2vh;
            }
            #tec_center {
                width: 45vh;
                height: 75vh;
                background: #fff;
            }
            #botoesc {
                height: 6vh;
                width: 45vh;
            }
            #cinco,
            #dois,
            #nove,
            #oito,
            #quatro,
            #seis,
            #sete,
            #tres,
            #um,
            #zero {
                background: #999;
            }
            #X {
                background: red;
            }
            #OK {
                background: #0f0;
            }
            body {
                font-family:Arial; 
                background-color: #a9a9a9;
                overflow: hidden;
                overflow-x: hidden;
                overflow-y: hidden;
                margin: 0;
                display: flex;
                justify-content: center;
            }
            .container-abas {
                display: flex;
                justify-content: center;
                text-align: center;
            }
            input.abas {
                display: none;
            }
            input.abas + label + div {
                display: flex;
                align-items: center;
                justify-content: flex-start;
                position: absolute;
                top: 15vh;
                width: 100vw;
                height: 83vh;
                opacity: 0;
                transition: opacity ease-in-out 0.3s;
                flex-direction: column;
                flex-wrap: wrap;
                align-content: stretch;
                padding-top: 2vh;
            }
            div p {
                font-family: sans-serif;
                font-size: 4rem;
                color: #fff;
            }
            input.abas:checked + label + div {
                opacity: 1;
                z-index: 100;
            }
            input.abas + label {
                line-height: 28px;
                cursor: pointer;
                transition: ease-in-out 0.3s;
            }
            .labelaba {
                width: 20vw;
                height: 15vh;
                display: flex;
                background-color: silver;
                justify-content: center;
                align-items: center;
            }
            input.abas:checked + label {
                background-color: #a9a9a9;
            }
            svg {
                width: 10vh;
                height: 10vw;
            }
            #div_b2{
              width: 150px;
              height: 75px;
              font-size:18px; 
              font-family:Arial; 
              margin:10px; 
              background-color:lightgray;
              display:flex;
              flex-direction: column;
              align-items: center;
              border-radius: 4px;
            }                   
        </style>
        <script type="text/javascript">
            function clicked() {
                if (!confirm("Tem certeza que deseja carregar um novo programa?")) return !1;
                window.location = "/ota";
            }
            function preenche(e) {
                var t = (elemento = document.getElementById("campo")).value;
                elemento.value = t + e;
            }
            function set_teclado(e) {
                (document.getElementById("tec_geral_d").style.display = "flex"), (desc_timers = e), (document.getElementById("desc_t").innerText = desc_timers);
            }
            function close_tec() {
                (elemento = document.getElementById("campo")), (desc_timers = ""), (elemento.value = ""), (document.getElementById("desc_t").innerText = ""), (document.getElementById("tec_geral_d").style.display = "none");
            }
            function send_tec() {
                (hab_send = ""),
                    "" != (elemento = document.getElementById("campo")).value && (hab_send = "{" + desc_timers + ":" + elemento.value + "}"),
                    console.log(hab_send),
                    connection.send(hab_send),
                    (elemento.value = ""),
                    (desc_timers = ""),
                    (document.getElementById("desc_t").innerText = ""),
                    (document.getElementById("tec_geral_d").style.display = "none");
            }
            var cont = 10,
                connection = new WebSocket("ws://" + location.hostname + ":81/");
            function reduz() {
                cont > 1 && (cont -= 1),
                    cont < 2 && (console.log("conexao perdida"), document.location.reload(!0)),
                    setTimeout(function () {
                        reduz();
                    }, 200);
            }
            function send_ckbx(e) {
                document.getElementById(e).checked ? (connection.send('{"' + e + '":"off"}'), console.log('{"' + e + '":"off"}')) : (connection.send('{"' + e + '":"on"}'), console.log('{"' + e + '":"on"}'));
            }
            function reset() {
                connection.send('{"reset":"on"}'), console.log('{"reset":"on"}');
            }
            function check(e) {
                "" == e.userid.value && "" == e.pwd.value ? window.open("/serverIndex") : alert("Error Password or Username");
            }
            (connection.onopen = function () {
                connection.send("Conectado");
            }),
                (connection.onmessage = function (e) {
                    var t = JSON.parse(e.data);
                    (cont = 10),
                        t.velocidade && (document.getElementById("vel_maq").innerText = t.velocidade),
                        "1" == t.flag_estado && ((document.body.style.backgroundColor = "#6fc57c"), (document.getElementById("flag_estado").checked = !0)),
                        "0" == t.flag_estado && ((document.body.style.backgroundColor = "#ff9295"), (document.getElementById("flag_estado").checked = !1)),
                        "1" == t.hab_balanca ? (document.getElementById("hab_balanca").checked = !0) : "0" == t.hab_balanca && (document.getElementById("hab_balanca").checked = !1),//botao inicial
                        "1" == t.hab_balanca ? (document.getElementById("hab_balanca2").checked = !0) : "0" == t.hab_balanca && (document.getElementById("hab_balanca2").checked = !1),//botao da aba2
                        "1" == t.hab_tracionador ? (document.getElementById("hab_tracionador").checked = !0) : "0" == t.hab_tracionador && (document.getElementById("hab_tracionador").checked = !1),
                        "1" == t.hab_tracionador ? (document.getElementById("hab_tracionador2").checked = !0) : "0" == t.hab_tracionador && (document.getElementById("hab_tracionador2").checked = !1),
                        "1" == t.hab_soldah ? (document.getElementById("hab_soldah").checked = !0) : "0" == t.hab_soldah && (document.getElementById("hab_soldah").checked = !1),
                        "1" == t.hab_faca ? (document.getElementById("hab_faca").checked = !0) : "0" == t.hab_faca && (document.getElementById("hab_faca").checked = !1),
                        "1" == t.hab_foto ? (document.getElementById("hab_foto").checked = !0) : "0" == t.hab_foto && (document.getElementById("hab_foto").checked = !1),
                        "1" == t.hab_soldav ? (document.getElementById("hab_soldav").checked = !0) : "0" == t.hab_soldav && (document.getElementById("hab_soldav").checked = !1),
                        "1" == t.hab_datador ? (document.getElementById("hab_datador").checked = !0) : "0" == t.hab_datador && (document.getElementById("hab_datador").checked = !1),
                        "1" == t.hab_temperaturav ? (document.getElementById("hab_temperaturav").checked = !0) : "0" == t.hab_temperaturav && (document.getElementById("hab_temperaturav").checked = !1),
                        "1" == t.hab_desbobinador ? (document.getElementById("hab_desbobinador").checked = !0) : "0" == t.hab_desbobinador && (document.getElementById("hab_desbobinador").checked = !1),
                        "1" == t.hab_resfriamento ? (document.getElementById("hab_resfriamento").checked = !0) : "0" == t.hab_resfriamento && (document.getElementById("hab_resfriamento").checked = !1),
                        "1" == t.hab_calha ? (document.getElementById("hab_calha").checked = !0) : "0" == t.hab_calha && (document.getElementById("hab_calha").checked = !1),
                        "1" == t.hab_calha ? (document.getElementById("hab_calha2").checked = !0) : "0" == t.hab_calha && (document.getElementById("hab_calha2").checked = !1),
                        "1" == t.hab_temperaturah ? (document.getElementById("hab_temperaturah").checked = !0) : "0" == t.hab_temperaturah && (document.getElementById("hab_temperaturah").checked = !1),
                        t.tracionador_liga && (document.getElementById("tracionador_liga").innerText = t.tracionador_liga),
                        t.tracionador_tempo && (document.getElementById("tracionador_tempo").innerText = t.tracionador_tempo),
                        t.shorizontal_liga && (document.getElementById("shorizontal_liga").innerText = t.shorizontal_liga),
                        t.shorizontal_tempo && (document.getElementById("shorizontal_tempo").innerText = t.shorizontal_tempo),
                        t.svertical_liga && (document.getElementById("svertical_liga").innerText = t.svertical_liga),
                        t.svertical_tempo && (document.getElementById("svertical_tempo").innerText = t.svertical_tempo),
                        t.balanca_liga && (document.getElementById("balanca_liga").innerText = t.balanca_liga),
                        t.balanca_tempo && (document.getElementById("balanca_tempo").innerText = t.balanca_tempo),
                        t.temperaturav_liga && (document.getElementById("temperaturav_liga").innerText = t.temperaturav_liga),
                        t.temperaturav_tempo && (document.getElementById("temperaturav_tempo").innerText = t.temperaturav_tempo),
                        t.faca_liga && (document.getElementById("faca_liga").innerText = t.faca_liga),
                        t.faca_tempo && (document.getElementById("faca_tempo").innerText = t.faca_tempo),
                        t.datador_liga && (document.getElementById("datador_liga").innerText = t.datador_liga),
                        t.datador_tempo && (document.getElementById("datador_tempo").innerText = t.datador_tempo),
                        t.resfriamento_liga && (document.getElementById("resfriamento_liga").innerText = t.resfriamento_liga),
                        t.resfriamento_tempo && (document.getElementById("resfriamento_tempo").innerText = t.resfriamento_tempo),
                        t.preaq_tempo && (document.getElementById("preaq_tempo").innerText = t.preaq_tempo),
                        t.alarme
                            ? ((document.getElementById("id_span_alarme").innerHTML = t.alarme), (document.getElementById("id_divgeral_alarme").style.display = "flex"))
                            : ((document.getElementById("id_span_alarme").innerText = t.alarme), (document.getElementById("id_divgeral_alarme").style.display = "none")),
                        console.log(t);
                }),
                (connection.onerror = function (e) {
                    console.log("WebSocket Error!!!", e), document.location.reload(!0);
                });
        </script>
    </head>
    <body onload="reduz()">
        <div class="class_divgeral_alarme" id="id_divgeral_alarme">
            <div class="class_div_alarme" id="id_div_alarme"><span id="id_span_alarme"> </span></div>
            <button class="button green" onclick="reset();">RESET</button>
        </div>
        <div class="tec_geral" id="tec_geral_d">
            <div id="c"><input readonly="readonly" type="text" id="campo" value="" /></div>
            <div id="desc_t"></div>
            <div id="botoes">
                <input type="button" id="sete" value="7" onclick="preenche(this.value);" /> <input type="button" id="oito" value="8" onclick="preenche(this.value);" />
                <input type="button" id="nove" value="9" onclick="preenche(this.value);" /> <input type="button" id="quatro" value="4" onclick="preenche(this.value);" />
                <input type="button" id="cinco" value="5" onclick="preenche(this.value);" /> <input type="button" id="seis" value="6" onclick="preenche(this.value);" />
                <input type="button" id="um" value="1" onclick="preenche(this.value);" /> <input type="button" id="dois" value="2" onclick="preenche(this.value);" />
                <input type="button" id="tres" value="3" onclick="preenche(this.value);" /> <input type="button" id="X" value="X" onclick="close_tec();" /> <input type="button" id="zero" value="0" onclick="preenche(this.value);" />
                <input type="button" id="OK" value="OK" onclick="send_tec();" />
            </div>
        </div>
        <section class="container-abas">
            <input type="radio" name="abas" class="abas" id="aba1" checked />
            <label for="aba1" class="labelaba">
                <svg xmlns="http://www.w3.org/2000/svg" width="90" height="79" viewBox="0 0 90 79" xmlns:v="https://vecta.io/nano">
                    <path
                        d="M72.625 77.418c1.566 0 2.773-1.219 2.773-2.801v-29.82h7.227c2.648 0 4.816-2.191 4.816-4.871 0-1.582-.723-2.922-1.805-3.773l-9.277-8.156V14.363c0-1.582-1.324-2.922-2.891-2.922h-5.902c-1.566 0-2.891 1.34-2.891 2.922v3.41L48.055 3.164a4.73 4.73 0 0 0-6.266 0L3.848 36.395c-1.566 1.34-2.051 3.41-1.328 5.355s2.531 3.168 4.457 3.168h7.23v29.82c0 1.582 1.203 2.801 2.77 2.801h16.262V55.75c0-3.043 2.41-5.598 5.539-5.598h12.047c3.012 0 5.539 2.434 5.539 5.598v21.668zm0 0"
                        fill="rgb(30%,30%,31%)"
                    />
                </svg>
            </label>
            <div>
            
                <div class="aba_home_e">
                  <div id="div_b2">BALANÇA<input type="checkbox" hidden="hidden" id="hab_balanca2" /> <label class="switch" onclick="send_ckbx('hab_balanca');"> </label> </div>
                  <div id="div_b2">TRACIONADOR<input type="checkbox" hidden="hidden" id="hab_tracionador2" /> <label class="switch" onclick="send_ckbx('hab_tracionador');"></label></div>
                  <div id="div_b2">CORREIAS<input type="checkbox" hidden="hidden" id="hab_calha2" /> <label class="switch" onclick="send_ckbx('hab_calha');"></label></div>
                </div>        
                <div class="aba_home_d">
                  <div class="toggle"><input type="checkbox" id="flag_estado" /> <label onclick="send_ckbx('flag_estado');"></label> START / STOP</div>
                </div>
            </div>
            <input type="radio" name="abas" class="abas" id="aba2" />
            <label for="aba2" class="labelaba">
                <svg xmlns="http://www.w3.org/2000/svg" width="90" height="90" viewBox="0 0 90 90" fill="rgb(30%,30%,31%)" xmlns:v="https://vecta.io/nano">
                    <path
                        d="M26.164 66.699h37.672C75.766 66.699 85.535 57 85.535 45s-9.699-21.699-21.699-21.699H26.164C14.234 23.301 4.465 33 4.465 45s9.77 21.699 21.699 21.699zm0-37.676h37.672c8.793 0 15.977 7.188 15.977 15.977s-7.184 15.977-15.977 15.977H26.164c-8.793 0-15.977-7.187-15.977-15.977s7.184-15.977 15.977-15.977zm0 28.047c6.625 0 12.07-5.441 12.07-12.07s-5.445-12.07-12.07-12.07-12.07 5.441-12.07 12.07 5.441 12.07 12.07 12.07zm0-18.418c3.488 0 6.348 2.859 6.348 6.348s-2.859 6.348-6.348 6.348-6.352-2.859-6.352-6.348 2.863-6.348 6.352-6.348zm0 0"
                    />
                </svg>
            </label>
            <div>
                <div class="checkbt">SOLDA HOR. <input type="checkbox" hidden="hidden" id="hab_soldah" /> <label class="switch" onclick="send_ckbx('hab_soldah');"></label></div>
                <div class="checkbt">SOLDA V. <input type="checkbox" hidden="hidden" id="hab_soldav" /> <label class="switch" onclick="send_ckbx('hab_soldav');"></label></div>
                <div class="checkbt">FACA <input type="checkbox" hidden="hidden" id="hab_faca" /> <label class="switch" onclick="send_ckbx('hab_faca');"></label></div>
                <div class="checkbt">RESFRIAMENTO <input type="checkbox" hidden="hidden" id="hab_resfriamento" /> <label class="switch" onclick="send_ckbx('hab_resfriamento');"></label></div>
                <div class="checkbt">DATADOR <input type="checkbox" hidden="hidden" id="hab_datador" /> <label class="switch" onclick="send_ckbx('hab_datador');"></label></div>
                <div class="checkbt">TEMP. VER <input type="checkbox" hidden="hidden" id="hab_temperaturav" /> <label class="switch" onclick="send_ckbx('hab_temperaturav');"></label></div>
                <div class="checkbt">TEMP. HOR <input type="checkbox" hidden="hidden" id="hab_temperaturah" /> <label class="switch" onclick="send_ckbx('hab_temperaturah');"></label></div>
                <div class="checkbt">TRACIONADOR <input type="checkbox" hidden="hidden" id="hab_tracionador" /> <label class="switch" onclick="send_ckbx('hab_tracionador');"></label></div>
                <div class="checkbt">BALANÇA <input type="checkbox" hidden="hidden" id="hab_balanca" /> <label class="switch" onclick="send_ckbx('hab_balanca');"></label></div>
                <div class="checkbt">DESBOBINADOR <input type="checkbox" hidden="hidden" id="hab_desbobinador" /> <label class="switch" onclick="send_ckbx('hab_desbobinador');"></label></div>
                <div class="checkbt">CORREIAS<input type="checkbox" hidden="hidden" id="hab_calha" /> <label class="switch" onclick="send_ckbx('hab_calha');"></label></div>
                <div class="checkbt">FOTOCÉLULA<input type="checkbox" hidden="hidden" id="hab_foto" /> <label class="switch" onclick="send_ckbx('hab_foto');"></label></div>
                
            </div>
            <input type="radio" name="abas" class="abas" id="aba3" />
            <label for="aba3" class="labelaba">
                <svg xmlns="http://www.w3.org/2000/svg" width="75" height="69" viewBox="0 0 75 69" fill="rgb(30%,30%,31%)" xmlns:v="https://vecta.io/nano">
                    <path
                        d="M73.34 35.699l-6.16-7.965c-.609-.719-1.496-1.133-2.43-1.133s-1.82.414-2.43 1.133l-6.16 7.965c-1.047 1.355-.809 3.313.531 4.375a3.06 3.06 0 0 0 4.324-.539l.219-.293C59.055 52.023 48.5 61.629 35.703 62.477s-24.5-7.285-28.312-19.668 1.27-25.797 12.281-32.445 25.094-4.789 34.059 4.484a3.06 3.06 0 0 0 4.242-.074 3.15 3.15 0 0 0 .164-4.289C47.043-.984 29.574-3.148 16.074 5.27S-3.367 30.441 1.777 45.621s19.996 24.723 35.766 22.992 28.25-14.285 30.051-30.227l.891 1.172a3.06 3.06 0 0 0 4.324.539c1.34-1.062 1.578-3.02.531-4.375zM33.914 12.672c-1.695.008-3.07 1.395-3.078 3.109v18.715a2.5 2.5 0 0 0 .094.723 2.3 2.3 0 0 0 .242.656 2.02 2.02 0 0 0 .336.559l.094.117c.129.156.277.293.438.41l.129.094L37 40.738l7.398 5.613c.531.41 1.184.629 1.852.621 1.324-.004 2.5-.863 2.918-2.137s-.012-2.668-1.066-3.477l-.984-.75-3.953-2.992-4.094-3.121L37 32.938V15.781c-.008-1.719-1.387-3.109-3.086-3.109zm0 0"
                    />
                </svg>
            </label>
            <div>
                <div id="timers" align="center">
                    <div class="edit_times">
                        <a class="atimes">S. HORIZONTAL</a> <br />
                        <a class="atimes">LIGA=</a><span id="shorizontal_liga" class="spantimes">----</span>&nbsp;&nbsp;&nbsp; <a class="atimes">TEMPO=</a>
                        <span id="shorizontal_tempo" onclick="set_teclado('shorizontal_tempo');" class="spantimes">----</span>
                    </div>
                    <div class="edit_times">
                        <a class="atimes">S. VERTICAL</a> <br />
                        <a class="atimes">LIGA=</a><span id="svertical_liga" onclick="set_teclado('svertical_liga');" class="spantimes">----</span>&nbsp;&nbsp;&nbsp; <a class="atimes">TEMPO=</a>
                        <span id="svertical_tempo" onclick="set_teclado('svertical_tempo');" class="spantimes">----</span>
                    </div>
                    <div class="edit_times">
                        <a class="atimes">FACA</a> <br />
                        <a class="atimes">LIGA=</a><span id="faca_liga" onclick="set_teclado('faca_liga');" class="spantimes">----</span>&nbsp;&nbsp;&nbsp; <a class="atimes">TEMPO=</a>
                        <span id="faca_tempo" onclick="set_teclado('faca_tempo');" class="spantimes">----</span>
                    </div>
                    <div class="edit_times">
                        <a class="atimes">RESFRIAMENTO</a> <br />
                        <a class="atimes">LIGA=</a><span id="resfriamento_liga" onclick="set_teclado('resfriamento_liga');" class="spantimes">----</span>&nbsp;&nbsp;&nbsp; <a class="atimes">TEMPO=</a>
                        <span id="resfriamento_tempo" onclick="set_teclado('resfriamento_tempo');" class="spantimes">----</span>
                    </div>
                    <div class="edit_times">
                        <a class="atimes">DATADOR</a> <br />
                        <a class="atimes">LIGA=</a><span id="datador_liga" onclick="set_teclado('datador_liga');" class="spantimes">----</span>&nbsp;&nbsp;&nbsp; <a class="atimes">TEMPO=</a>
                        <span id="datador_tempo" onclick="set_teclado('datador_tempo');" class="spantimes">----</span>
                    </div>
                    <div class="edit_times">
                        <a class="atimes">TEMP. VERTICAL</a> <br />
                        <a class="atimes">LIGA=</a><span id="temperaturav_liga" onclick="set_teclado('temperaturav_liga');" class="spantimes">----</span>&nbsp;&nbsp;&nbsp; <a class="atimes">TEMPO=</a>
                        <span id="temperaturav_tempo" onclick="set_teclado('temperaturav_tempo');" class="spantimes">----</span>
                    </div>
                    <div class="edit_times">
                        <a class="atimes">TRACIONADOR</a> <br />
                        <a class="atimes">LIGA=</a><span id="tracionador_liga" onclick="set_teclado('tracionador_liga');" class="spantimes">----</span>&nbsp;&nbsp;&nbsp; <a class="atimes">TEMPO=</a>
                        <span id="tracionador_tempo" onclick="set_teclado('tracionador_tempo');" class="spantimes">----</span>
                    </div>
                    <div class="edit_times">
                        <a class="atimes">BALANÇA</a> <br />
                        <a class="atimes">T. QUEDA=</a><span id="balanca_liga" onclick="set_teclado('balanca_liga');" class="spantimes">----</span>&nbsp;&nbsp;&nbsp; <a class="atimes">TEMPO=</a>
                        <span id="balanca_tempo" onclick="set_teclado('balanca_tempo');" class="spantimes">----</span>
                    </div>
                </div>
            </div>
            <input type="radio" name="abas" class="abas" id="aba4" />
            <label for="aba4" class="labelaba">
                <svg xmlns="http://www.w3.org/2000/svg" width="85" height="85" viewBox="0 0 85 85" xmlns:v="https://vecta.io/nano">
                    <path
                        d="M71.047 27.836c-1.625-1.348-3.113-.473-4.09.301-5.062 4.012-9.328 7.152-13.898 10.613l-15.82 12.215c-4.246 3.395-5.23 8.051-2.707 12.777.707 1.539 2.363 2.906 4.547 3.75 1.082.43 2.238.656 3.406.664 3.031 0 5.828-1.633 7.969-4.742l11.754-17.512 9.059-13.816c1.09-1.605 1.008-3.234-.219-4.25zm0 0"
                        fill="rgb(30%,30%,31%)"
                    />
                    <path
                        d="M42.5 25.285a32.7 32.7 0 0 1 12.324 3.617l1.664.945 1.648-1.301 6.695-5.297a42 42 0 0 0-6.051-3.121l-1.223-.492c-12.867-4.949-27.344-3.25-38.711 4.547S.688 44.879.676 58.664h3.75a37.46 37.46 0 0 1 3.977-14.117 36.4 36.4 0 0 1 8.836-11.145 35.09 35.09 0 0 1 12.039-6.668 33.9 33.9 0 0 1 13.223-1.449zm41.824 33.379l-.012-.812.008-.34-.391-4.867a41.26 41.26 0 0 0-7.727-18.906l-3.055 4.496-4.113 6.063c.406.961.762 1.945 1.063 2.941a29.35 29.35 0 0 1 1.094 11.426zm0 0"
                        fill="rgb(38%,38%,39%)"
                    />
                </svg>
            </label>
            <div class="div_velocidade">
                <a class="vel">VEL</a> <br />
                <span id="vel_maq" onclick="set_teclado('velocidade');">----</span>
                <br>
                <div class="edit_times">
                   <a class="atimes">PRÉ-AQUECIMENTO</a> <br />
                   <a class="atimes">TEMPO=</a><span id="preaq_tempo" onclick="set_teclado('preaq_tempo');" class="spantimes">----</span>
                </div>
            </div>
            <input type="radio" name="abas" class="abas" id="aba5" />
            <label for="aba5" class="labelaba">
                <svg
                    xmlns="http://www.w3.org/2000/svg"
                    width="85"
                    height="85"
                    viewBox="0 0 85 85"
                    fill="none"
                    stroke-linecap="round"
                    stroke-linejoin="round"
                    stroke="rgb(30%,30%,30%)"
                    stroke-miterlimit="10"
                    stroke-width="5.313"
                    xmlns:v="https://vecta.io/nano"
                >
                    <path d="M53.125 42.5A10.63 10.63 0 0 1 42.5 53.125 10.63 10.63 0 0 1 31.875 42.5 10.63 10.63 0 0 1 42.5 31.875 10.63 10.63 0 0 1 53.125 42.5zm0 0" />
                    <path
                        d="M73.73 27.535l-2.656-4.602a5.31 5.31 0 0 0-7.254-1.945l-1.398.809c-5.312 3.066-11.953-.766-11.953-6.902v-1.613c0-2.934-2.379-5.312-5.312-5.312h-5.312c-2.934 0-5.312 2.379-5.312 5.313v1.613c0 6.137-6.641 9.969-11.953 6.902l-1.398-.809a5.31 5.31 0 0 0-7.254 1.945l-2.656 4.602c-1.469 2.543-.598 5.789 1.941 7.258l1.398.805c5.313 3.07 5.313 10.734 0 13.805l-1.398.805c-2.539 1.469-3.41 4.715-1.941 7.258l2.656 4.602a5.31 5.31 0 0 0 7.254 1.945l1.398-.809c5.313-3.066 11.953.766 11.953 6.902v1.613c0 2.934 2.379 5.313 5.313 5.313h5.313c2.934 0 5.313-2.379 5.313-5.312v-1.613c0-6.137 6.641-9.969 11.953-6.902l1.398.809a5.31 5.31 0 0 0 7.254-1.945l2.656-4.602c1.469-2.543.598-5.789-1.941-7.258l-1.398-.805c-5.312-3.07-5.312-10.734 0-13.805l1.398-.805c2.539-1.469 3.41-4.715 1.941-7.258zm0 0"
                    />
                </svg>
            </label>
            <div>
                <p><input type="submit" value="Atualizar Programa" class="button" onclick="clicked();" /></p>
            </div>
        </section>
    </body>
</html>

)=====";
char html_ota[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="pt-br">
<style>
body {
    margin: 0px;
    font-family: Arial;
  background-color:#bbb;
}
#div1{
    display: flex;
    align-items: center;
    flex-direction: column;
    text-align: center;
}
#div2 {
    display: flex;
    text-align: initial;
}
.button {
  background-color: green; 
  border: none;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}

.buttonv {  
  background-color: gray; 
}

::-webkit-file-upload-button {
  background-color: #555555; 
  border: none;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
</style>

 <script>
 function aguarde(){
  document.getElementById("idh2").innerHTML = "Aguarde o carregamento do Programa...";
  document.getElementById("idh2").style.color = "#FF0000";
 }
 function voltar(){
   window.location='/';
 }
</script>
<head>
<meta charset="utf-8"/>
<meta name="viewport" content="width=device-width, user-scalable=no">
</head>
<body>
        <div id="div1">
          <h1>Atualização do software da maquina</h1>
          <h2 id="idh2">Selecione o arquivo para a atualização e clique em atualizar.</h2>
      <div id="div2">
          <form method='POST' action='/update' enctype='multipart/form-data'>
          <p><input type='file' name='update' ></p>
          <p><input type='submit' value='Atualizar' onclick="aguarde();" class="button"></p>
          <p><input type='submit' value='Voltar' onclick="voltar();" class="button buttonv"></p>
          </form>
    </div>
        </div>
</body>
</html>
 )=====";




char html_pos_ota[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="pt-br">
<head>
<meta charset="utf-8"/>
<meta name="viewport" content="width=device-width, user-scalable=no">
<script>
  function myFunction() {
    setTimeout(function(){ window.location='/'; }, 30000);
  }
</script>
</head>
<body onload="myFunction()">
    <h2>Atualização do software realizada</h1>
    <h3>Reiniciando a clp, tenha um pouco de paciência...</h2>
</body>
</html>
 )=====";



 
