//#define DRAW_CONTOURS
//#define DRAW_FOUR_CONTOURS
#include <opencv2/opencv.hpp>
#include <iostream>
#include <Exchangestation.h>
#include "camera.h"
#define DRAW_RRT
//��ֹ����
//һ��Ҫ���ÿ��ͼ�Ƿ�Ϸ�
//�������������ֱ�ӽ�������Ҳ�����ˣ�ֻ��ҪԤ�鵽�˴�
//��ôת��Ϊ��������
//�����ļ�
using namespace std;
using namespace cv;

int all = 0;
int loss = 0;
bool issent=false;
float tradius;
Point2f result_point(0,0);
Point2f last_point(0,0);
//  TODO Ȼ��������ϵ����ϵת��
//  TODO ����ͨѶ
//  TODO ���������������roll��
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
            //�ȼ�¼��һ֡
            last_point=result_point;
            /// ��ȡͼƬ
            camera_warrper->read_frame_rgb(src);
            Mat t=src;
            resize(src, src, Size(640, 512));
            demo->changeMat(src);
            result_point=demo->process(&tradius);
            //�����صĵ�Ƿ�
            if(result_point.x==0||result_point.y==0  ){
                result_point=last_point;
                loss++;
            }
            /// ��ԭ��ԭͼ
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

///  Ȼ��������ϵ����ϵת��
///  ����ͨѶ
///  ���������������roll��

int main() {

    VideoCapture video("../Video.mp4");
    Mat frame;
    int color = Red;
    station *demo=new station;
    demo->setinfo(frame,color);
    if (video.isOpened())
    {
        cout << "��Ƶ��ͼ��Ŀ��=" << video.get(CAP_PROP_FRAME_WIDTH) << endl;
        cout << "��Ƶ��ͼ��ĸ߶�=" << video.get(CAP_PROP_FRAME_HEIGHT) << endl;
        cout << "��Ƶ֡��=" << video.get(CAP_PROP_FPS) << endl;
        cout << "��Ƶ����֡��=" << video.get(CAP_PROP_FRAME_COUNT);
    }
    else
    {
        cout << "��ȷ����Ƶ�ļ������Ƿ���ȷ" << endl;
        return -1;
    }
    while (1)
    {

        video.read(frame);
        if (frame.empty())
        {
            break;
        }
        /// resize����֮��Ҫ�������ǵ�����ͷ���е������ͺ˵Ĵ�С����׷���ٶȣ�ֻ׷��׼��
        /// ��ʱ�ǽ���resize
        //cout<<"origin size: "<<frame.size()<<endl;
        Mat t=frame;
        resize(frame, frame, Size(640, 512));
        imshow("frame",frame);

        double time_count = (double)getTickCount();

        //�ȼ�¼��һ֡
        last_point=result_point;
        demo->changeMat(frame);
        result_point = demo->process( &tradius);

        if(result_point.x==0||result_point.y==0  ){
            result_point=last_point;
            loss++;
        }
        /// ֱ��2����ԭ�᲻��ֲܴ�
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
