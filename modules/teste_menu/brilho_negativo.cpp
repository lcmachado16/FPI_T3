#include <opencv2/opencv.hpp>

int main() {
    cv::VideoCapture cap(0);  // Captura de vídeo da câmera (pode variar dependendo do dispositivo)

    if (!cap.isOpened()) {
        std::cerr << "Erro ao abrir a câmera!" << std::endl;
        return -1;
    }

    bool init = true;
    int operation = 0;

    while (true) {
        cv::Mat frame;
        cap >> frame;

        if (frame.empty()) {
            std::cerr << "Erro ao capturar o frame!" << std::endl;
            break;
        }

        int pressed_key = cv::waitKey(1);

        if (pressed_key == 27) {  // Se a tecla Esc (27) for pressionada, sai do loop
            break;
        } else if (pressed_key == '1') {
            // Ajuste de brilho
            frame.convertTo(frame, -1, 1.2, 0);
        } else if (pressed_key == '2') {
            // Ajuste de contraste
            frame.convertTo(frame, -1, 2.0, 0);
        } else if (pressed_key == '3') {
            // Obter o negativo do vídeo
            cv::Mat negated_frame;
            cv::bitwise_not(frame, negated_frame);
            frame = negated_frame;
        } else if (pressed_key == '4') {
            // Aplica o mesmo tratamento que '1' (Ajuste de brilho, por exemplo)
            frame.convertTo(frame, -1, 1.2, 0);
        }

        // Exibe o frame resultante
        cv::imshow("Video", frame);
    }

    return 0;
}
