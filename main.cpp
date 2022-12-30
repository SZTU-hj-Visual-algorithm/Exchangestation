//#define DRAW_CONTOURS
//#define DRAW_FOUR_CONTOURS
#include <opencv2/opencv.hpp>
#include <iostream>
#include <Exchangestation.h>
#include "camera.h"
#define DRAW_RRT
//防止死机
//一定要检查每张图是否合法
//发送完这次命令直接结束，再也不发了，只需要预瞄到此处
//怎么转换为世界坐标
//工程文件
using namespace std;
using namespace cv;

int all = 0;
int loss = 0;
bool issent=false;
float tradius;
Point2f result_point(0,0);
Point2f last_point(0,0);
//  TODO 然后还有坐标系坐标系转换
//  TODO 串口通讯
//  TODO 如果可以怎样结算roll轴
/*int main()
{
    auto camera_warrper = new Camera;
    Mat src;
    station *demo=new station;
    int color=Red;
    demo->setinfo(src,color);
    if (camera_warrper->init())
    {
        cout<<"okkkkkkkkkkkkkkkkkkkkkkkkkk"<<endl;
        while(true)
        {
            cout<<"right!!!!!!!!!!!!!!!!!!!!!!"<<endl;
           cout<<src.size()<<endl;
            //先记录上一帧
            last_point=result_point;
            /// 读取图片
            camera_warrper->read_frame_rgb(src);
            Mat t=src;
            resize(src, src, Size(640, 512));
            demo->changeMat(src);
            result_point=demo->process(&tradius);
            //若返回的点非法
            if(result_point.x==0||result_point.y==0  ){
                result_point=last_point;
                loss++;
            }
            /// 还原到原图
            Point2f tp(result_point.x*2,result_point.y*2);
            circle(t,tp,tradius,Scalar(255,100,100),2);
            circle(t,tp,5,Scalar(255,160,125),-1);
            imshow("tp",t);
            cout<<"result_point is: "<<result_point<<endl;



            imshow("src",src);
            if (waitKey(10) == 27)
            {
                camera_warrper->~Camera();
                break;
            }
        }
    }
    else{
        cout<<"no camera!!!!\n";
    }
    return 0;
}*/

///  然后还有坐标系坐标系转换
///  串口通讯
///  如果可以怎样结算roll轴

int main() {

    VideoCapture video("../Video.mp4");
    Mat frame;
    int color = Red;
    station *demo=new station;
    demo->setinfo(frame,color);
    if (video.isOpened())
    {
        cout << "视频中图像的宽度=" << video.get(CAP_PROP_FRAME_WIDTH) << endl;
        cout << "视频中图像的高度=" << video.get(CAP_PROP_FRAME_HEIGHT) << endl;
        cout << "视频帧率=" << video.get(CAP_PROP_FPS) << endl;
        cout << "视频的总帧数=" << video.get(CAP_PROP_FRAME_COUNT);
    }
    else
    {
        cout << "请确认视频文件名称是否正确" << endl;
        return -1;
    }
    while (1)
    {

        video.read(frame);
        if (frame.empty())
        {
            break;
        }
        /// resize这里之后要根据我们的摄像头进行调节膨胀核的大小，不追求速度，只追求准。
        /// 暂时是进行resize
        //cout<<"origin size: "<<frame.size()<<endl;
        Mat t=frame;
        resize(frame, frame, Size(640, 512));
        imshow("frame",frame);

        double time_count = (double)getTickCount();

        //先记录上一帧
        last_point=result_point;
        demo->changeMat(frame);
        result_point = demo->process( &tradius);

        if(result_point.x==0||result_point.y==0  ){
            result_point=last_point;
            loss++;
        }
        /// 直接2倍还原会不会很粗糙
        Point2f tp(result_point.x*2,result_point.y*2);
        circle(t,tp,tradius,Scalar(255,100,100),2);
        circle(t,tp,5,Scalar(255,160,125),-1);
        imshow("tp",t);
        cout<<"ALL_time is: "<<((double)getTickCount() - time_count)/1000<<endl;
        cout<<"result_point is: "<<result_point<<endl;
    }
    cout <<"loss is: "<< loss << endl;
    return 0;
}
