import { Html5Qrcode } from "html5-qrcode";

document.getElementById('startButton').addEventListener('click', function() {
    const html5QrCode = new Html5Qrcode("reader");

    

    function onScanSuccess(decodedText, decodedResult) {
        document.getElementById('qrResult').value = decodedText;
        html5QrCode.stop().then((ignore) => {
            // QR Code scanning is stopped.
        }).catch((err) => {
            console.error("Stop failed: ", err);
        });
    }

    document.getElementById('startButton').addEventListener('click', function() {
      navigator.mediaDevices.getUserMedia({ video: true })
        .then(stream => {
          const video = document.getElementById('reader');
          if (video) {
            video.srcObject = stream;
          } else {
            console.error('Elemento <video> não encontrado.');
          }
        })
        .catch(error => {
          console.error('Erro ao acessar a câmera:', error);
        });
    });

    function onScanFailure(error) {
        console.warn(`Code scan error = ${error}`);
    }

    if (!navigator.mediaDevices || !navigator.mediaDevices.getUserMedia) {
        alert("Streaming de câmera não suportado pelo navegador.");
        return;
    }

    navigator.mediaDevices.getUserMedia({ video: true })
        .then(stream => {
            html5QrCode.start(
                { facingMode: "environment" }, // Use rear camera
                {
                    fps: 50,    // Optional, frame per seconds for qr code scanning
                    qrbox: { width: 250, height: 250 }  // Optional, if you want bounded box UI
                },
                onScanSuccess,
                onScanFailure
            ).catch((err) => {
                console.error("Unable to start scanning: ", err);
            });
        })
        .catch(err => {
            console.error("Error accessing the camera: ", err);
            alert("Erro ao acessar a câmera: " + err.message);
        });
});
