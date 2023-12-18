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
            init = false;
            operation = 1;
        } else if (pressed_key == '2') {
            init = false;
            operation = 2;
        }

        // Aplica as operações conforme necessário
        if (operation == 1) {
            // Operação GAUSSIAN BLUR
            cv::GaussianBlur(frame, frame, cv::Size(5, 5), 0);
        } else if (operation == 2) {
            // Operação CANNY
            cv::Mat detected_edges;
            int lowThreshold = 50;
            double ratio = 3.0;
            int kernel_size = 3;

            cv::Canny(frame, detected_edges, lowThreshold, lowThreshold * ratio, kernel_size);

            // Substitua o frame original pelos bordas detectadas
            //frame = cv::Scalar::all(0);
            //frame.setTo(cv::Scalar(0, 255, 0), detected_edges);
            frame = detected_edges;
        }

        // Exibe o frame resultante
        cv::imshow("Video", frame);
    }

    return 0;
}
