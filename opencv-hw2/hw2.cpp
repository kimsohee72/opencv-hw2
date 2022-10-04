#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void print_RGB(Mat image) {
    unsigned char* pData = (unsigned char*)image.data;

    for (int row = 0; row < image.rows; row++)
    {
        for (int col = 0; col < image.cols; col++)
        {
            uchar b = pData[row * image.cols * 3 + col * 3];
            uchar g = pData[row * image.cols * 3 + col * 3 + 1];
            uchar r = pData[row * image.cols * 3 + col * 3 + 2];

            printf("(x:%d, y:%d) : RGB[%d, %d, %d]\n", col, row, r, g, b);

        }

    }
}

Mat make_YUV(Mat image) {

    Mat r_img_out(image.rows, image.cols, CV_8UC1, Scalar(0));
    Mat b_img_out(image.rows, image.cols, CV_8UC1, Scalar(0));
    Mat y_img_out(image.rows, image.cols, CV_8UC1, Scalar(0));
    Mat yuv_img_out(image.rows, image.cols, CV_8UC3, Scalar(0));

    unsigned char* pData = (unsigned char*)image.data;

    for (int row = 0; row < image.rows; row++)
    {
        for (int col = 0; col < image.cols; col++)
        {
            uchar b = pData[row * image.cols * 3 + col * 3];
            uchar g = pData[row * image.cols * 3 + col * 3 + 1];
            uchar r = pData[row * image.cols * 3 + col * 3 + 2];
            int y = 0.257 * (int)r + 0.098 * (int)b + 0.504 * (int)g + 16;
            int u = -(0.148 * (int)r) + 0.439 * (int)b - 0.291 * (int)g + 128;
            int v = 0.439 * (int)r - 0.071 * (int)b - 0.368 * (int)g + 128;

            yuv_img_out.data[row * yuv_img_out.cols * 3 + col * 3 + 2] = v;
            yuv_img_out.data[row * yuv_img_out.cols * 3 + col * 3 + 1] = u;
            yuv_img_out.data[row * yuv_img_out.cols * 3 + col * 3] = y;

        }

    }
    return yuv_img_out;

}

Mat slicing_face(Mat image) {
    Mat f_img_out(image.rows, image.cols, CV_8UC1, Scalar(0));
    Mat face_img_out(image.rows, image.cols, CV_8UC3, Scalar(0));

    unsigned char* pData = (unsigned char*)image.data;

    for (int row = 0; row < image.rows; row++)
    {
        for (int col = 0; col < image.cols; col++)
        {
            uchar b = pData[row * image.cols * 3 + col * 3];
            uchar g = pData[row * image.cols * 3 + col * 3 + 1];
            uchar r = pData[row * image.cols * 3 + col * 3 + 2];

            if (190 < (int)r && (int)r < 250 && 150 < (int)g && (int)g < 230 && 130 < (int)b && (int)b < 230) {
                face_img_out.data[row * face_img_out.cols * 3 + col * 3 + 2] = (int)r;
                face_img_out.data[row * face_img_out.cols * 3 + col * 3 + 1] = (int)g;
                face_img_out.data[row * face_img_out.cols * 3 + col * 3] = (int)b;
            }
            else {
                face_img_out.data[row * face_img_out.cols * 3 + col * 3 + 2] = 0;
                face_img_out.data[row * face_img_out.cols * 3 + col * 3 + 1] = 0;
                face_img_out.data[row * face_img_out.cols * 3 + col * 3] = 0;
            }



        }

    }
    return face_img_out;
}


Mat bw_face(Mat image) {
    Mat f_img_out(image.rows, image.cols, CV_8UC1, Scalar(0));
    Mat face_img_out(image.rows, image.cols, CV_8UC3, Scalar(0));

    unsigned char* pData = (unsigned char*)image.data;

    for (int row = 0; row < image.rows; row++)
    {
        for (int col = 0; col < image.cols; col++)
        {
            uchar b = pData[row * image.cols * 3 + col * 3];
            uchar g = pData[row * image.cols * 3 + col * 3 + 1];
            uchar r = pData[row * image.cols * 3 + col * 3 + 2];

            if (190 < (int)r && (int)r < 250 && 150 < (int)g && (int)g < 230 && 130 < (int)b && (int)b < 230) {
                f_img_out.data[row * face_img_out.cols + col] = 255;
            }
            else {
                f_img_out.data[row * face_img_out.cols + col] = 0;
            }



        }

    }
    return f_img_out;
}

int main() {
    Mat image, image_YUV;
    int a;
    image = imread("p.png");
    Mat picture = imread("picture.jpg");

    cvtColor(image, image_YUV, COLOR_BGR2YUV);
    printf("이미지로 하고 싶은 작업을 선택해 주세요\n1.RGB값 받아오기 2.RGB이미지->YUV이미지 3.이미지 슬라이싱 4.흑백이미지\n");
    cin >> a;
    switch (a) {
    case 1:
        print_RGB(picture);
        imshow("input image", picture);
        moveWindow("input image", 500, 100);
        break;
    case 2:
        imshow("input image", image);
        imshow("YUV image", image_YUV);
        imshow("Make YUV image", make_YUV(image));
        moveWindow("input image", 100, 100);
        moveWindow("YUV image", 400, 100);
        moveWindow("Make YUV image", 700, 100);
        break;
    case 3:
        imshow("input image", image);
        imshow("Slicing_Face", slicing_face(image));
        moveWindow("input image", 100, 100);
        moveWindow("Slicing_Face", 400, 100);
        break;
    case 4:
        imshow("input image", image);
        imshow("Face", bw_face(image));
        moveWindow("input image", 100, 100);
        moveWindow("Face", 400, 100);
        break;
    }

    waitKey(0);
    return 0;
}
