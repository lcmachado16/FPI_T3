#include <opencv2/opencv.hpp>

int main() {
    cv::VideoCapture cap(0);

    if (!cap.isOpened()) {
        std::cerr << "Erro ao abrir a câmera!" << std::endl;
        return -1;
    }

    int codec = cv::VideoWriter::fourcc('D', 'I', 'V', 'X');  // Codec DIVX
    double fps = 20.0;
    cv::Size frameSize(640, 480);

    cv::VideoWriter out("output.avi", codec, fps, frameSize);

    if (!out.isOpened()) {
        std::cerr << "Erro ao abrir o VideoWriter!" << std::endl;
        return -1;
    }

    cv::Mat frame, gray, edges;

    while (true) {
        cap >> frame;

        if (frame.empty()) {
            std::cerr << "Erro ao capturar o frame!" << std::endl;
            break;
        }

        // Converta para tons de cinza
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // Aplica o filtro Canny
        cv::Canny(gray, edges, 50, 150);

        // Mescla a imagem original com as bordas (outra opção é salvar apenas as bordas)
        cv::cvtColor(edges, edges, cv::COLOR_GRAY2BGR);
        cv::addWeighted(frame, 0.7, edges, 0.3, 0, frame);

        // Escreve o frame no vídeo
        out.write(frame);

        // Exibe o frame na tela (opcional)
        cv::imshow("Frame", frame);

        // Verifica se o usuário pressionou a tecla 'q'
        if (cv::waitKey(30) == 'q') {
            break;
        }
    }

    cap.release();
    out.release();
    cv::destroyAllWindows();

    return 0;
}
