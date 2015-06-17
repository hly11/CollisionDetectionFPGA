 #include "top.h"

#define MAX_HEIGHT 480
#define MAX_WIDTH 640

void Resize_Test (
		hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1>	    &_src,
		hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1>	&_dst, int ROWS, int COLS, int DROWS, int DCOLS );

void Resize_Test (
		hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1>	    &_src,
		hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1>	&_dst, int ROWS, int COLS, int DROWS, int DCOLS )
{
    hls::LineBuffer<2,MAX_WIDTH+1,hls::Scalar<1,float> >	    k_buf;
    hls::Window<2,2,hls::Scalar<1,float> >   win;
    short     dcols=_dst.cols;
    short     drows=_dst.rows;
    short     srows=_src.rows;
    short     scols=_src.cols;
    ap_fixed<32,16,AP_RND>    	row_rate=((ap_fixed<32,16,AP_RND> )srows)/(ap_fixed<32,16,AP_RND>)drows;
    ap_fixed<32,16,AP_RND>    	col_rate=((ap_fixed<32,16,AP_RND> )scols)/(ap_fixed<32,16,AP_RND>)dcols;
    ap_fixed<20,2,AP_RND>	u,v, u1,v1;

    hls::Scalar<1,float> s, temp, d;
    ap_fixed<4,2,AP_RND> 		par=0.5;
    ap_fixed<20,10,AP_RND> 		offset_row=row_rate/2-par;
    ap_fixed<20,10,AP_RND> 		offset_col=col_rate/2-par;
    ap_fixed<32,16,AP_RND> 		fx=0;
    ap_fixed<32,16,AP_RND> 		fy=0;

    short     rows= (drows+1);
    short     cols= (dcols+1);

    short x=0;
    short pre_fy=-10;
    short pre_fx=-10;
    bool row_rd=false;
    bool row_wr=false;

    for(short i= 0;i<rows;i++) {
        for(short j= 0;j<cols;j++) {
#pragma HLS LOOP_FLATTEN OFF
#pragma HLS DEPENDENCE array inter false
#pragma HLS PIPELINE

            bool col_rd=false;
            bool col_wr=false;

            short dy = row_rate>1 ? (short)(i/row_rate):(i-1);
            short dx = col_rate>1 ? (short)(j/col_rate):(j-1);

            fy =(dy)*row_rate+offset_row;
            fx =(dx)*col_rate+offset_col;

            short sx=(short)fx;
            short sy=(short)fy;
            if(fx-sx>0)
                u=fx-sx;
            else
                u=0;
            if(fy-sy>0)
                v=fy-sy;
            else
                v=0;
            u1=1-u;
            v1=1-v;
            if(sx>scols-1)
            {
                sx=scols-1;
                u=0;
            }
            if(sy>srows-1)
            {
                sy=srows-1;
                v=0;
            }
            if(j==0)
            {
                x=0;
                pre_fx=-10;
                if(row_rate>1)
                {
                    row_rd=true;
                    row_wr= (sy==(i-1)) ? true : false;
                }
                else
                {
                    if(i==0){
                        row_rd=true;
                    }
                    else if(sy!=pre_fy)
                    {
                        row_rd=true;
                        pre_fy=sy;
                    }
                    else {
                        row_rd=false;
                    }
                    row_wr= i>0? true: false;
                }
            }
            if(col_rate>1)
            {
                col_rd=true;
                col_wr= (sx==(j-1)) ? true : false;
            }else{
                if(j==0){
                    col_rd=true;
                }
                else if(sx!=pre_fx)
                {
                    col_rd=true;
                    pre_fx=sx;
                }
                else
                    col_rd=false;
                col_wr= j>0? true: false;
            }
            if(col_rd)
            {
                for(int r= 0;r<2;r++)
                {
                    win.val[r][1]=win.val[r][0];
                }
                if(row_rd)
                {

                    k_buf.val[1][x]=k_buf.val[0][x];
                    win.val[1][0]=k_buf.val[0][x];
                    if(sy<srows-1&&sx<scols-1)
                    {
                        _src >> s;
                        k_buf.val[0][x]=s;
                        win.val[0][0]=k_buf.val[0][x];
                    }
                    else if(sx>=scols-1&&sy<srows-1){
                        k_buf.val[0][x]=s;//border
                    }
                    else if(sy>=srows-1){
                        win.val[0][0]=k_buf.val[0][x];
                    }
                }
                else
                {
                    for(int r= 0;r<2;r++)
                    {
                        win.val[r][0]=k_buf.val[r][x];
                    }
                }

                x++;
            }
            if(row_wr && col_wr)
            {
                for(int k=0;k<1;k++)
                {
                    typename hls::filter2d_traits<float, ap_fixed<15,1,AP_RND> ,4>::ACCUM_T t=0;
                    //typedef typename hls::fixed_type<float>::T SRCT;
                    typedef hls::filter2d_traits<float, ap_fixed<15,1,AP_RND> ,4>::ACCUM_T SRCT;

                    t=((SRCT)win.val[1][1].val[k])*u1*v1+
                        ((SRCT)win.val[1][0].val[k])*v1*u+
                        ((SRCT)win.val[0][1].val[k])*u1*v+
                        ((SRCT)win.val[0][0].val[k])*u*v;
                    d.val[k]=hls::sr_cast<float>(t);
                }
                _dst << d;
            }
        }
    }
}

template<int IMG_H, int IMG_W, int SIZE> void PadImage(hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1> &in, hls::Mat<MAX_HEIGHT+51, MAX_WIDTH+51, HLS_32FC1> &out)
{
	//float temp;
	hls::Scalar<1, float> temp;
	static float linebuffer[IMG_W];
	float output;
	//#pragma HLS ARRAY_PARTITION variable=linebuffer complete dim=1
	//hls::Scalar<1, float> linebuffer[IMG_W];
	for(int i=0;i<IMG_H+SIZE;i++)
	{
		for(int asd=0;asd<IMG_W+SIZE;asd++)
		{
			#pragma HLS PIPELINE
			if(i<IMG_H)
			{
				if(asd<IMG_W)
				{
					//temp = in.read();
					temp = in.read();
					if(i==IMG_H-1)
						linebuffer[asd]=temp.val[0];
				}

				//out << temp;
				output = temp.val[0];
			}
			else
			{
				if(asd<IMG_W)
				{
					//hls::Scalar<1, float> outputte(linebuffer[asd]);
					//out << output;
					output = linebuffer[asd];
				}
				else
					output = temp.val[0];
			}
			out << output;
		}
	}
}
/*
float CalculateOutput(float A, float B, float C, float D, float E, float F, float G, float H, float I, float J,  float K, float L, float M, float N, float O, float P, float Q, float R,  float S, float T, float U, float V,  float W, float X, float Y, float Z, float Z1, float Z2, float Z3, float Z4, float Z5, float Z6, float inverse_area)
{
#pragma HLS inline
	float Dxx_9 = A - B - C + D - (E - F - G + H) - (E - F - G + H) - (E - F - G + H);
			//if(r==2&&c==4)std::cerr<<"dxx"<<Dxx_9<<std::endl;
			float Dyy_9 = I - J - K + L - (M - N - O + P) - (M - N - O + P) - (M - N - O + P);
			//if(r==2&&c==4)std::cerr<<"Dyy_9 "<<Dyy_9<<std::endl;
			float Dxy_9 = (Q - R - S + T) + (U - V - W + X) - (Y - Z - Z1 + Z2) - (Z3 - Z4 - Z5 + Z6);
			//if(r==2&&c==4)std::cerr<<"Dxy_9 "<<Dxy_9<<std::endl;
			Dxx_9 *= inverse_area;
			Dyy_9 *= inverse_area;
			Dxy_9 *= inverse_area;

			//hls::Scalar<1, float> output;
			//output.val[0]=(Dxx_9 * Dyy_9 - 0.81f * Dxy_9 * Dxy_9);
			return (Dxx_9 * Dyy_9 - 0.81f * Dxy_9 * Dxy_9);
}*/
/*
#define IMG_HEIGHT (IMG_H+FILTER_SIZE)
#define IMG_WIDTH (IMG_W+FILTER_SIZE)
#define BORDER ((FILTER_SIZE+3)/6)
#define LOBE (FILTER_SIZE/3)
#define DX_TOP (2*LOBE-1)*/
//#define MAX_HEIGHT 1080//#define MAX_WIDTH 1920



template<int IMG_H, int IMG_W> void FilterTest(hls::Mat<MAX_HEIGHT+51, MAX_WIDTH+51, HLS_32FC1> &in, hls::Mat<MAX_HEIGHT+51, MAX_WIDTH+51, HLS_32FC1> &out, int FILTER_SIZE)
{
	//const int IMG_HEIGHT = IMG_H+FILTER_SIZE;
	//const int IMG_WIDTH = IMG_W+FILTER_SIZE;

	//static float linebuf[(FILTER_SIZE+1)*(IMG_W+FILTER_SIZE)];
	//static shift_reg<(FILTER_SIZE+1)*(IMG_W+FILTER_SIZE)> linebuf;
	/*hls::LineBuffer<9+1,IMG_W+9,float,0> linebuf_9;
	hls::Window<9+1, 9+1, float> linebuf2_9;

	hls::LineBuffer<15+1,IMG_W+15,float,0> linebuf_15;
	hls::Window<15+1, 15+1, float> linebuf2_15;

	hls::LineBuffer<21+1,IMG_W+21,float,0> linebuf_21;
	hls::Window<21+1, 21+1, float> linebuf2_21;

	hls::LineBuffer<27+1,IMG_W+27,float,0> linebuf_27;
	hls::Window<27+1, 27+1, float> linebuf2_27;

	hls::LineBuffer<39+1,IMG_W+39,float,0> linebuf_39;
	hls::Window<39+1, 39+1, float> linebuf2_39;*/

	hls::LineBuffer<51+1,IMG_W+51,float> linebuf_51;
	hls::Window<51+1, 51+1, float> linebuf2_51;

		//		hls::LineBuffer<FILTER_SIZE+1,IMG_WIDTH,float,0> linebuf;
		//			hls::Window<FILTER_SIZE+1, FILTER_SIZE+1, float> linebuf2;
	//static ap_shift_reg<float, (FILTER_SIZE+1)*(IMG_W+FILTER_SIZE)> linebuf;
	//#pragma HLS ARRAY_PARTITION variable=linebuf complete dim=1

	//hls::Scalar<1, float> buffer

	//const float inverse_area = 1.f/(FILTER_SIZE*FILTER_SIZE);
	const float inverse_area_9 = 0.012345679012346f;
	const float inverse_area_15 = 0.004444444444444f;
	const float inverse_area_21 = 0.002267573696145f;
	const float inverse_area_27 = 0.001371742112483f;
	const float inverse_area_39 = 0.0006574621959237344f;
	const float inverse_area_51 = 0.0003844675124951942f;
	const int b = (FILTER_SIZE - 1) / 2;             // border for this filter
	const int l = (FILTER_SIZE / 3);                   // lobe for this filter (filter size / 3)
	const int w = FILTER_SIZE;                       // filter size

/*
	for(int count=0;count<((FILTER_SIZE+1)/2)*IMG_WIDTH+((FILTER_SIZE+1)/2);count++)
	{
		#pragma HLS pipeline
		hls::Scalar<1, float> temp;
		in >> temp;
		linebuf.shift(temp.val[0]);
	}
*/

	int r=0;
	int c=0;
	int row=0;
	int col=0;
	const int loopcount=(IMG_H+51)*(IMG_W+51);
	hls::Scalar<1, float> temp;
	float temp2;

	for(int count=0;count<loopcount+(((51+1)/2)*(IMG_W+51)+((51+1)/2));count++)
	{
		#pragma HLS pipeline rewind

		if(count==(((51+1)/2)*(IMG_W+51)+((51+1)/2)))
		{
			r=0;
			c=0;
		}

		if(count<loopcount)
			in >> temp;
		else
			temp.val[0]=0.0f;
/*
		if(FILTER_SIZE==9)
		{
		linebuf_9.shift_down(col);
		temp2 = linebuf_9.getval(0,col);
		linebuf_9.insert_bottom(temp.val[0], col);

		linebuf2_9.shift_right();
		for(int i=FILTER_SIZE;i>=2;--i)
		{
			#pragma HLS unroll
			linebuf2_9.insert(linebuf_9.getval(i,col),i,0);
		}
		/*
		linebuf2.insert(linebuf.getval(9,col),9,0);
		linebuf2.insert(linebuf.getval(8,col),8,0);
		linebuf2.insert(linebuf.getval(7,col),7,0);
		linebuf2.insert(linebuf.getval(6,col),6,0);
		linebuf2.insert(linebuf.getval(5,col),5,0);
		linebuf2.insert(linebuf.getval(4,col),4,0);
		linebuf2.insert(linebuf.getval(3,col),3,0);
		linebuf2.insert(linebuf.getval(2,col),2,0);*\
		linebuf2_9.insert(temp2,1,0);
		linebuf2_9.insert(temp.val[0],0,0);
		} */

		linebuf_51.shift_down(col);
		temp2 = linebuf_51.getval(0,col);
		linebuf_51.insert_bottom(temp.val[0], col);

		linebuf2_51.shift_right();
		for(int i=51;i>=2;--i)
		{
			#pragma HLS unroll
			linebuf2_51.insert(linebuf_51.getval(i,col),i,0);
		}

		linebuf2_51.insert(temp2,1,0);
		linebuf2_51.insert(temp.val[0],0,0);


		//if(count==0)
		//	std::cerr<<buffer[0];

		//float A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, Z1, Z2, Z3, Z4, Z5, Z6;
		float A=0.0f;
		float B=0.0f;
		float C=0.0f;
		float D=0.0f;
		float E=0.0f;
		float F=0.0f;
		float G=0.0f;
		float H=0.0f;
		float I=0.0f;
		float J=0.0f;
		float K=0.0f;
		float L=0.0f;
		float M=0.0f;
		float N=0.0f;
		float O=0.0f;
		float P=0.0f;
		float Q=0.0f;
		float R=0.0f;
		float S=0.0f;
		float T=0.0f;
		float U=0.0f;
		float V=0.0f;
		float W=0.0f;
		float X=0.0f;
		float Y=0.0f;
		float Z=0.0f;
		float Z1=0.0f;
		float Z2=0.0f;
		float Z3=0.0f;
		float Z4=0.0f;
		float Z5=0.0f;
		float Z6=0.0f;

		int row_1 = r - l + 1;
		int col_1 = c - b;
		int row_2 = r + l;
		int col_2 = c - b + w;
		int col_3 = c - l/2;
		int col_4 = c - l/2 + l;
		int row_3 = r - b;
		int col_5 = c - l + 1;
		int row_4 = r - b + w;
		int col_6 = c + l;
		int row_5 = r - l / 2;
		int row_6 = r - l / 2 + l;
		int row_7 = r - l;
		int col_7 = c + 1;
		int row_8 = r;
		int col_8 = c + 1 + l;
		int row_9 = r + 1;
		int col_9 = c - l;
		int row_10 = r + 1 + l;
		int col_10 = c;
		/*
		int r1 = min_1(row_1,          IMG_HEIGHT) - 1;
		int c1 = min_1(col_1,          IMG_WIDTH)  - 1;
		int r2 = min_1(row_2,   IMG_HEIGHT) - 1;
		int c2 = min_1(col_2,   IMG_WIDTH)  - 1;
		int r3 = min_1(row_3,          IMG_HEIGHT) - 1;
		int c3 = min_1(col_3,          IMG_WIDTH)  - 1;
		int r4 = min_1(row_4,   IMG_HEIGHT) - 1;
		int c4 = min_1(col_4,   IMG_WIDTH)  - 1;
		int r5 = min_1(row_5,          IMG_HEIGHT) - 1;
		int c5 = min_1(col_5,          IMG_WIDTH)  - 1;
		int r6 = min_1(row_6,   IMG_HEIGHT) - 1;
		int c6 = min_1(col_6,   IMG_WIDTH)  - 1;
		int r7 = min_1(row_7,          IMG_HEIGHT) - 1;
		int c7 = min_1(col_7,          IMG_WIDTH)  - 1;
		int r8 = min_1(row_8,   IMG_HEIGHT) - 1;
		int c8 = min_1(col_8,   IMG_WIDTH)  - 1;
		int r9 = min_1(row_9,          IMG_HEIGHT) - 1;
		int c9 = min_1(col_9,          IMG_WIDTH)  - 1;
		int r10 = min_1(row_10,   IMG_HEIGHT) - 1;int c10 = min_1(col_10,   IMG_WIDTH) - 1;
		*/
		int r1 = row_1 - 1;
		int c1 = col_1 - 1;
		int r2 = row_2 - 1;
		int c2 = col_2 - 1;
		int r3 = row_3 - 1;
		int c3 = col_3 - 1;
		int r4 = row_4 - 1;
		int c4 = col_4 - 1;
		int r5 = row_5 - 1;
		int c5 = col_5 - 1;
		int r6 = row_6 - 1;
		int c6 = col_6 - 1;
		int r7 = row_7 - 1;
		int c7 = col_7 - 1;
		int r8 = row_8 - 1;
		int c8 = col_8 - 1;
		int r9 = row_9 - 1;
		int c9 = col_9 - 1;
		int r10 = row_10 - 1;int c10 = col_10 - 1;

		if(FILTER_SIZE==9)
		{
		/*
		if (r1 >= 0 && c1 >= 0) A = linebuf.read(DX_TOP*IMG_WIDTH+FILTER_SIZE+BORDER*IMG_WIDTH);
		if (r1 >= 0 && c2 >= 0) B = linebuf.read(DX_TOP*IMG_WIDTH+BORDER*IMG_WIDTH);
		if (r2 >= 0 && c1 >= 0) C = linebuf.read(FILTER_SIZE+BORDER*IMG_WIDTH);
		if (r2 >= 0 && c2 >= 0) D = linebuf.read(0+BORDER*IMG_WIDTH);

		if (r1 >= 0 && c3 >= 0) E = linebuf.read(DX_TOP*IMG_WIDTH+(FILTER_SIZE-LOBE)+BORDER*IMG_WIDTH);
		if (r1 >= 0 && c4 >= 0) F = linebuf.read(DX_TOP*IMG_WIDTH+LOBE+BORDER*IMG_WIDTH);
		if (r2 >= 0 && c3 >= 0) G = linebuf.read((FILTER_SIZE-LOBE)+BORDER*IMG_WIDTH);
		if (r2 >= 0 && c4 >= 0) H = linebuf.read(LOBE+BORDER*IMG_WIDTH);

		if (r3 >= 0 && c5 >= 0) I = linebuf.read(FILTER_SIZE*IMG_WIDTH+(FILTER_SIZE-BORDER));
		if (r3 >= 0 && c6 >= 0) J = linebuf.read(FILTER_SIZE*IMG_WIDTH+BORDER);
		if (r4 >= 0 && c5 >= 0) K = linebuf.read(FILTER_SIZE-BORDER);
		if (r4 >= 0 && c6 >= 0) L = linebuf.read(BORDER);

		if (r5 >= 0 && c5 >= 0) M = linebuf.read((FILTER_SIZE-LOBE)*IMG_WIDTH+(FILTER_SIZE-BORDER));
		if (r5 >= 0 && c6 >= 0) N = linebuf.read((FILTER_SIZE-LOBE)*IMG_WIDTH+BORDER);
		if (r6 >= 0 && c5 >= 0) O = linebuf.read(LOBE*IMG_WIDTH+(FILTER_SIZE-BORDER));
		if (r6 >= 0 && c6 >= 0) P = linebuf.read(LOBE*IMG_WIDTH+BORDER);

		if (r7 >= 0 && c7 >= 0) Q = linebuf.read((FILTER_SIZE-(BORDER-1))*IMG_WIDTH+BORDER-1+LOBE);
		if (r7 >= 0 && c8 >= 0) R = linebuf.read((FILTER_SIZE-(BORDER-1))*IMG_WIDTH+BORDER-1);
		if (r8 >= 0 && c7 >= 0) S = linebuf.read((FILTER_SIZE-(BORDER-1)-LOBE)*IMG_WIDTH+BORDER-1+LOBE);
		if (r8 >= 0 && c8 >= 0) T = linebuf.read((FILTER_SIZE-(BORDER-1)-LOBE)*IMG_WIDTH+BORDER-1);

		if (r9 >= 0 && c9 >= 0) U = linebuf.read((BORDER-1+LOBE)*IMG_WIDTH+(FILTER_SIZE-(BORDER-1)));
		if (r9 >= 0 && c10 >= 0) V = linebuf.read((BORDER-1+LOBE)*IMG_WIDTH+(FILTER_SIZE-(BORDER-1)-LOBE));
		if (r10 >= 0 && c9 >= 0) W = linebuf.read((BORDER-1)*IMG_WIDTH+(FILTER_SIZE-(BORDER-1)));
		if (r10 >= 0 && c10 >= 0) X = linebuf.read((BORDER-1)*IMG_WIDTH+(FILTER_SIZE-(BORDER-1)-LOBE));

		if (r7 >= 0 && c9 >= 0) Y = linebuf.read((FILTER_SIZE-(BORDER-1))*IMG_WIDTH+(FILTER_SIZE-(BORDER-1)));
		if (r7 >= 0 && c10 >= 0) Z = linebuf.read((FILTER_SIZE-(BORDER-1))*IMG_WIDTH+(FILTER_SIZE-(BORDER-1)-LOBE));
		if (r8 >= 0 && c9 >= 0) Z1 = linebuf.read((FILTER_SIZE-(BORDER-1)-LOBE)*IMG_WIDTH+(FILTER_SIZE-(BORDER-1)));
		if (r8 >= 0 && c10 >= 0) Z2 = linebuf.read((FILTER_SIZE-(BORDER-1)-LOBE)*IMG_WIDTH+(FILTER_SIZE-(BORDER-1)-LOBE));

		if (r9 >= 0 && c7 >= 0) Z3 = linebuf.read((LOBE+BORDER-1)*IMG_WIDTH+BORDER-1+LOBE);
		if (r9 >= 0 && c8 >= 0) Z4 = linebuf.read((LOBE+BORDER-1)*IMG_WIDTH+BORDER-1);
		if (r10 >= 0 && c7 >= 0) Z5 = linebuf.read((BORDER-1)*IMG_WIDTH+BORDER-1+LOBE);
		if (r10 >= 0 && c8 >= 0) Z6 = linebuf.read((BORDER-1)*IMG_WIDTH+BORDER-1);
		*/

		if (r1 >= 0 && c1 >= 0) A = linebuf2_51.getval(28,30);
		if (r1 >= 0 && c2 >= 0) B = linebuf2_51.getval(28,21);
		if (r2 >= 0 && c1 >= 0) C = linebuf2_51.getval(23,30);
		if (r2 >= 0 && c2 >= 0) D = linebuf2_51.getval(23,21);

		if (r1 >= 0 && c3 >= 0) E = linebuf2_51.getval(28,27);
		if (r1 >= 0 && c4 >= 0) F = linebuf2_51.getval(28,24);
		if (r2 >= 0 && c3 >= 0) G = linebuf2_51.getval(23,27);
		if (r2 >= 0 && c4 >= 0) H = linebuf2_51.getval(23,24);

		if (r3 >= 0 && c5 >= 0) I = linebuf2_51.getval(30,28);
		if (r3 >= 0 && c6 >= 0) J = linebuf2_51.getval(30,23);
		if (r4 >= 0 && c5 >= 0) K = linebuf2_51.getval(21,28);
		if (r4 >= 0 && c6 >= 0) L = linebuf2_51.getval(21,23);

		if (r5 >= 0 && c5 >= 0) M = linebuf2_51.getval(27,28);
		if (r5 >= 0 && c6 >= 0) N = linebuf2_51.getval(27,23);
		if (r6 >= 0 && c5 >= 0) O = linebuf2_51.getval(24,28);
		if (r6 >= 0 && c6 >= 0) P = linebuf2_51.getval(24,23);

		if (r7 >= 0 && c7 >= 0) Q = linebuf2_51.getval(29,25);
		if (r7 >= 0 && c8 >= 0) R = linebuf2_51.getval(29,22);
		if (r8 >= 0 && c7 >= 0) S = linebuf2_51.getval(26,25);
		if (r8 >= 0 && c8 >= 0) T = linebuf2_51.getval(26,22);

		if (r9 >= 0 && c9 >= 0) U = linebuf2_51.getval(25,29);
		if (r9 >= 0 && c10 >= 0) V = linebuf2_51.getval(25,26);
		if (r10 >= 0 && c9 >= 0) W = linebuf2_51.getval(22,29);
		if (r10 >= 0 && c10 >= 0) X = linebuf2_51.getval(22,26);

		if (r7 >= 0 && c9 >= 0) Y = linebuf2_51.getval(29,29);
		if (r7 >= 0 && c10 >= 0) Z = linebuf2_51.getval(29,26);
		if (r8 >= 0 && c9 >= 0) Z1 = linebuf2_51.getval(26,29);
		if (r8 >= 0 && c10 >= 0) Z2 = linebuf2_51.getval(26,26);

		if (r9 >= 0 && c7 >= 0) Z3 = linebuf2_51.getval(25,25);
		if (r9 >= 0 && c8 >= 0) Z4 = linebuf2_51.getval(25,22);
		if (r10 >= 0 && c7 >= 0) Z5 = linebuf2_51.getval(22,25);
		if (r10 >= 0 && c8 >= 0) Z6 = linebuf2_51.getval(22,22);

		}
		else if(FILTER_SIZE==15)
		{
					if (r1 >= 0 && c1 >= 0) A = 	linebuf2_51.getval(30,33);
					if (r1 >= 0 && c2 >= 0) B = 	linebuf2_51.getval(30,18);
					if (r2 >= 0 && c1 >= 0) C = 	linebuf2_51.getval(21,33);
					if (r2 >= 0 && c2 >= 0) D = 	linebuf2_51.getval(21,18);
					if (r1 >= 0 && c3 >= 0) E = 	linebuf2_51.getval(30,28);
					if (r1 >= 0 && c4 >= 0) F = 	linebuf2_51.getval(30,23);
					if (r2 >= 0 && c3 >= 0) G = 	linebuf2_51.getval(21,28);
					if (r2 >= 0 && c4 >= 0) H = 	linebuf2_51.getval(21,23);
					if (r3 >= 0 && c5 >= 0) I = 	linebuf2_51.getval(33,30);
					if (r3 >= 0 && c6 >= 0) J = 	linebuf2_51.getval(33,21);
					if (r4 >= 0 && c5 >= 0) K = 	linebuf2_51.getval(18,30);
					if (r4 >= 0 && c6 >= 0) L = 	linebuf2_51.getval(18,21);
					if (r5 >= 0 && c5 >= 0) M = 	linebuf2_51.getval(28,30);
					if (r5 >= 0 && c6 >= 0) N = 	linebuf2_51.getval(28,21);
					if (r6 >= 0 && c5 >= 0) O = 	linebuf2_51.getval(23,30);
					if (r6 >= 0 && c6 >= 0) P = 	linebuf2_51.getval(23,21);
					if (r7 >= 0 && c7 >= 0) Q = 	linebuf2_51.getval(31,25);
					if (r7 >= 0 && c8 >= 0) R = 	linebuf2_51.getval(31,20);
					if (r8 >= 0 && c7 >= 0) S = 	linebuf2_51.getval(26,25);
					if (r8 >= 0 && c8 >= 0) T = 	linebuf2_51.getval(26,20);
					if (r9 >= 0 && c9 >= 0) U = 	linebuf2_51.getval(25,31);
					if (r9 >= 0 && c10 >= 0) V = 	linebuf2_51.getval(25,26);
					if (r10 >= 0 && c9 >= 0) W = 	linebuf2_51.getval(20,31);
					if (r10 >= 0 && c10 >= 0) X =	linebuf2_51.getval(20,26);
					if (r7 >= 0 && c9 >= 0) Y = 	linebuf2_51.getval(31,31);
					if (r7 >= 0 && c10 >= 0) Z =	linebuf2_51.getval(31,26);
					if (r8 >= 0 && c9 >= 0) Z1 = 	linebuf2_51.getval(26,31);
					if (r8 >= 0 && c10 >= 0) Z2 = 	linebuf2_51.getval(26,26);
					if (r9 >= 0 && c7 >= 0) Z3 = 	linebuf2_51.getval(25,25);
					if (r9 >= 0 && c8 >= 0) Z4 = 	linebuf2_51.getval(25,20);
					if (r10 >= 0 && c7 >= 0) Z5 = 	linebuf2_51.getval(20,25);
					if (r10 >= 0 && c8 >= 0) Z6 = 	linebuf2_51.getval(20,20);
		}
		else if(FILTER_SIZE==21)
		{
					if (r1 >= 0 && c1 >= 0) A = 	linebuf2_51.getval(32,36);
					if (r1 >= 0 && c2 >= 0) B = 	linebuf2_51.getval(32,15);
					if (r2 >= 0 && c1 >= 0) C = 	linebuf2_51.getval(19,36);
					if (r2 >= 0 && c2 >= 0) D = 	linebuf2_51.getval(19,15);
					if (r1 >= 0 && c3 >= 0) E = 	linebuf2_51.getval(32,29);
					if (r1 >= 0 && c4 >= 0) F = 	linebuf2_51.getval(32,22);
					if (r2 >= 0 && c3 >= 0) G = 	linebuf2_51.getval(19,29);
					if (r2 >= 0 && c4 >= 0) H = 	linebuf2_51.getval(19,22);
					if (r3 >= 0 && c5 >= 0) I = 	linebuf2_51.getval(36,32);
					if (r3 >= 0 && c6 >= 0) J = 	linebuf2_51.getval(36,19);
					if (r4 >= 0 && c5 >= 0) K = 	linebuf2_51.getval(15,32);
					if (r4 >= 0 && c6 >= 0) L = 	linebuf2_51.getval(15,19);
					if (r5 >= 0 && c5 >= 0) M = 	linebuf2_51.getval(29,32);
					if (r5 >= 0 && c6 >= 0) N = 	linebuf2_51.getval(29,19);
					if (r6 >= 0 && c5 >= 0) O = 	linebuf2_51.getval(22,32);
					if (r6 >= 0 && c6 >= 0) P = 	linebuf2_51.getval(22,19);
					if (r7 >= 0 && c7 >= 0) Q = 	linebuf2_51.getval(33,25);
					if (r7 >= 0 && c8 >= 0) R = 	linebuf2_51.getval(33,18);
					if (r8 >= 0 && c7 >= 0) S = 	linebuf2_51.getval(26,25);
					if (r8 >= 0 && c8 >= 0) T = 	linebuf2_51.getval(26,18);
					if (r9 >= 0 && c9 >= 0) U = 	linebuf2_51.getval(25,33);
					if (r9 >= 0 && c10 >= 0) V = 	linebuf2_51.getval(25,26);
					if (r10 >= 0 && c9 >= 0) W = 	linebuf2_51.getval(18,33);
					if (r10 >= 0 && c10 >= 0) X =	linebuf2_51.getval(18,26);
					if (r7 >= 0 && c9 >= 0) Y = 	linebuf2_51.getval(33,33);
					if (r7 >= 0 && c10 >= 0) Z =	linebuf2_51.getval(33,26);
					if (r8 >= 0 && c9 >= 0) Z1 = 	linebuf2_51.getval(26,33);
					if (r8 >= 0 && c10 >= 0) Z2 = 	linebuf2_51.getval(26,26);
					if (r9 >= 0 && c7 >= 0) Z3 = 	linebuf2_51.getval(25,25);
					if (r9 >= 0 && c8 >= 0) Z4 = 	linebuf2_51.getval(25,18);
					if (r10 >= 0 && c7 >= 0) Z5 = 	linebuf2_51.getval(18,25);
					if (r10 >= 0 && c8 >= 0) Z6 = 	linebuf2_51.getval(18,18);
		}
		else if(FILTER_SIZE==27)
		{
					if (r1 >= 0 && c1 >= 0) A = 	linebuf2_51.getval(34,39);
					if (r1 >= 0 && c2 >= 0) B = 	linebuf2_51.getval(34,12);
					if (r2 >= 0 && c1 >= 0) C = 	linebuf2_51.getval(17,39);
					if (r2 >= 0 && c2 >= 0) D = 	linebuf2_51.getval(17,12);
					if (r1 >= 0 && c3 >= 0) E = 	linebuf2_51.getval(34,30);
					if (r1 >= 0 && c4 >= 0) F = 	linebuf2_51.getval(34,21);
					if (r2 >= 0 && c3 >= 0) G = 	linebuf2_51.getval(17,30);
					if (r2 >= 0 && c4 >= 0) H = 	linebuf2_51.getval(17,21);
					if (r3 >= 0 && c5 >= 0) I = 	linebuf2_51.getval(39,34);
					if (r3 >= 0 && c6 >= 0) J = 	linebuf2_51.getval(39,17);
					if (r4 >= 0 && c5 >= 0) K = 	linebuf2_51.getval(12,34);
					if (r4 >= 0 && c6 >= 0) L = 	linebuf2_51.getval(12,17);
					if (r5 >= 0 && c5 >= 0) M = 	linebuf2_51.getval(30,34);
					if (r5 >= 0 && c6 >= 0) N = 	linebuf2_51.getval(30,17);
					if (r6 >= 0 && c5 >= 0) O = 	linebuf2_51.getval(21,34);
					if (r6 >= 0 && c6 >= 0) P = 	linebuf2_51.getval(21,17);
					if (r7 >= 0 && c7 >= 0) Q = 	linebuf2_51.getval(35,25);
					if (r7 >= 0 && c8 >= 0) R = 	linebuf2_51.getval(35,16);
					if (r8 >= 0 && c7 >= 0) S = 	linebuf2_51.getval(26,25);
					if (r8 >= 0 && c8 >= 0) T = 	linebuf2_51.getval(26,16);
					if (r9 >= 0 && c9 >= 0) U = 	linebuf2_51.getval(25,35);
					if (r9 >= 0 && c10 >= 0) V = 	linebuf2_51.getval(25,26);
					if (r10 >= 0 && c9 >= 0) W = 	linebuf2_51.getval(16,35);
					if (r10 >= 0 && c10 >= 0) X =	linebuf2_51.getval(16,26);
					if (r7 >= 0 && c9 >= 0) Y = 	linebuf2_51.getval(35,35);
					if (r7 >= 0 && c10 >= 0) Z =	linebuf2_51.getval(35,26);
					if (r8 >= 0 && c9 >= 0) Z1 = 	linebuf2_51.getval(26,35);
					if (r8 >= 0 && c10 >= 0) Z2 = 	linebuf2_51.getval(26,26);
					if (r9 >= 0 && c7 >= 0) Z3 = 	linebuf2_51.getval(25,25);
					if (r9 >= 0 && c8 >= 0) Z4 = 	linebuf2_51.getval(25,16);
					if (r10 >= 0 && c7 >= 0) Z5 = 	linebuf2_51.getval(16,25);
					if (r10 >= 0 && c8 >= 0) Z6 = 	linebuf2_51.getval(16,16);
		}
		else if(FILTER_SIZE==39)
		{
					if (r1 >= 0 && c1 >= 0) A = 	linebuf2_51.getval(38,45);
					if (r1 >= 0 && c2 >= 0) B = 	linebuf2_51.getval(38,6);
					if (r2 >= 0 && c1 >= 0) C = 	linebuf2_51.getval(13,45);
					if (r2 >= 0 && c2 >= 0) D = 	linebuf2_51.getval(13,6);
					if (r1 >= 0 && c3 >= 0) E = 	linebuf2_51.getval(38,32);
					if (r1 >= 0 && c4 >= 0) F = 	linebuf2_51.getval(38,19);
					if (r2 >= 0 && c3 >= 0) G = 	linebuf2_51.getval(13,32);
					if (r2 >= 0 && c4 >= 0) H = 	linebuf2_51.getval(13,19);
					if (r3 >= 0 && c5 >= 0) I = 	linebuf2_51.getval(45,38);
					if (r3 >= 0 && c6 >= 0) J = 	linebuf2_51.getval(45,13);
					if (r4 >= 0 && c5 >= 0) K = 	linebuf2_51.getval(6,38);
					if (r4 >= 0 && c6 >= 0) L = 	linebuf2_51.getval(6,13);
					if (r5 >= 0 && c5 >= 0) M = 	linebuf2_51.getval(32,38);
					if (r5 >= 0 && c6 >= 0) N = 	linebuf2_51.getval(32,13);
					if (r6 >= 0 && c5 >= 0) O = 	linebuf2_51.getval(19,38);
					if (r6 >= 0 && c6 >= 0) P = 	linebuf2_51.getval(19,13);
					if (r7 >= 0 && c7 >= 0) Q = 	linebuf2_51.getval(39,25);
					if (r7 >= 0 && c8 >= 0) R = 	linebuf2_51.getval(39,12);
					if (r8 >= 0 && c7 >= 0) S = 	linebuf2_51.getval(26,25);
					if (r8 >= 0 && c8 >= 0) T = 	linebuf2_51.getval(26,12);
					if (r9 >= 0 && c9 >= 0) U = 	linebuf2_51.getval(25,39);
					if (r9 >= 0 && c10 >= 0) V = 	linebuf2_51.getval(25,26);
					if (r10 >= 0 && c9 >= 0) W = 	linebuf2_51.getval(12,39);
					if (r10 >= 0 && c10 >= 0) X =	linebuf2_51.getval(12,26);
					if (r7 >= 0 && c9 >= 0) Y = 	linebuf2_51.getval(39,39);
					if (r7 >= 0 && c10 >= 0) Z =	linebuf2_51.getval(39,26);
					if (r8 >= 0 && c9 >= 0) Z1 = 	linebuf2_51.getval(26,39);
					if (r8 >= 0 && c10 >= 0) Z2 = 	linebuf2_51.getval(26,26);
					if (r9 >= 0 && c7 >= 0) Z3 = 	linebuf2_51.getval(25,25);
					if (r9 >= 0 && c8 >= 0) Z4 = 	linebuf2_51.getval(25,12);
					if (r10 >= 0 && c7 >= 0) Z5 = 	linebuf2_51.getval(12,25);
					if (r10 >= 0 && c8 >= 0) Z6 = 	linebuf2_51.getval(12,12);
		}
		else if(FILTER_SIZE==51)
		{
					if (r1 >= 0 && c1 >= 0) A = 	linebuf2_51.getval(42,51);
					if (r1 >= 0 && c2 >= 0) B = 	linebuf2_51.getval(42,0);
					if (r2 >= 0 && c1 >= 0) C = 	linebuf2_51.getval(9,51);
					if (r2 >= 0 && c2 >= 0) D = 	linebuf2_51.getval(9,0);
					if (r1 >= 0 && c3 >= 0) E = 	linebuf2_51.getval(42,34);
					if (r1 >= 0 && c4 >= 0) F = 	linebuf2_51.getval(42,17);
					if (r2 >= 0 && c3 >= 0) G = 	linebuf2_51.getval(9,34);
					if (r2 >= 0 && c4 >= 0) H = 	linebuf2_51.getval(9,17);
					if (r3 >= 0 && c5 >= 0) I = 	linebuf2_51.getval(51,42);
					if (r3 >= 0 && c6 >= 0) J = 	linebuf2_51.getval(51,9);
					if (r4 >= 0 && c5 >= 0) K = 	linebuf2_51.getval(0,42);
					if (r4 >= 0 && c6 >= 0) L = 	linebuf2_51.getval(0,9);
					if (r5 >= 0 && c5 >= 0) M = 	linebuf2_51.getval(34,42);
					if (r5 >= 0 && c6 >= 0) N = 	linebuf2_51.getval(34,9);
					if (r6 >= 0 && c5 >= 0) O = 	linebuf2_51.getval(17,42);
					if (r6 >= 0 && c6 >= 0) P = 	linebuf2_51.getval(17,9);
					if (r7 >= 0 && c7 >= 0) Q = 	linebuf2_51.getval(43,25);
					if (r7 >= 0 && c8 >= 0) R = 	linebuf2_51.getval(43,8);
					if (r8 >= 0 && c7 >= 0) S = 	linebuf2_51.getval(26,25);
					if (r8 >= 0 && c8 >= 0) T = 	linebuf2_51.getval(26,8);
					if (r9 >= 0 && c9 >= 0) U = 	linebuf2_51.getval(25,43);
					if (r9 >= 0 && c10 >= 0) V = 	linebuf2_51.getval(25,26);
					if (r10 >= 0 && c9 >= 0) W = 	linebuf2_51.getval(8,43);
					if (r10 >= 0 && c10 >= 0) X =	linebuf2_51.getval(8,26);
					if (r7 >= 0 && c9 >= 0) Y = 	linebuf2_51.getval(43,43);
					if (r7 >= 0 && c10 >= 0) Z =	linebuf2_51.getval(43,26);
					if (r8 >= 0 && c9 >= 0) Z1 = 	linebuf2_51.getval(26,43);
					if (r8 >= 0 && c10 >= 0) Z2 = 	linebuf2_51.getval(26,26);
					if (r9 >= 0 && c7 >= 0) Z3 = 	linebuf2_51.getval(25,25);
					if (r9 >= 0 && c8 >= 0) Z4 = 	linebuf2_51.getval(25,8);
					if (r10 >= 0 && c7 >= 0) Z5 = 	linebuf2_51.getval(8,25);
					if (r10 >= 0 && c8 >= 0) Z6 = 	linebuf2_51.getval(8,8);
		}

		//float Dxx_9 = buffer[0+BORDER*IMG_WIDTH] - buffer[FILTER_SIZE+BORDER*IMG_WIDTH] - buffer[DX_TOP*IMG_WIDTH+BORDER*IMG_WIDTH] + buffer[DX_TOP*IMG_WIDTH+FILTER_SIZE+BORDER*IMG_WIDTH] - 3*buffer[LOBE+BORDER*IMG_WIDTH] + 3*buffer[(FILTER_SIZE-LOBE)+BORDER*IMG_WIDTH] + 3*buffer[DX_TOP*IMG_WIDTH+LOBE+BORDER*IMG_WIDTH] - 3*buffer[DX_TOP*IMG_WIDTH+(FILTER_SIZE-LOBE)+BORDER*IMG_WIDTH];
		//float Dyy_9 = buffer[BORDER] - buffer[FILTER_SIZE-BORDER] - buffer[FILTER_SIZE*IMG_WIDTH+BORDER] + buffer[FILTER_SIZE*IMG_WIDTH+(FILTER_SIZE-BORDER)] - 3*buffer[LOBE*IMG_WIDTH+BORDER] + 3*buffer[LOBE*IMG_WIDTH+(FILTER_SIZE-BORDER)] + 3*buffer[(FILTER_SIZE-LOBE-1)*IMG_WIDTH+BORDER] - 3*buffer[(FILTER_SIZE-LOBE-1)*IMG_WIDTH+(FILTER_SIZE-BORDER)];
		//float Dxy_9 = - buffer[(BORDER-1)*IMG_WIDTH+BORDER-1] + buffer[(BORDER-1)*IMG_WIDTH+BORDER-1+LOBE] + buffer[(LOBE+BORDER-1)*IMG_WIDTH+BORDER-1] - buffer[(LOBE+BORDER-1)*IMG_WIDTH+BORDER-1+LOBE] + buffer[(FILTER_SIZE-(BORDER-1)-LOBE)*IMG_WIDTH+BORDER-1] - buffer[(FILTER_SIZE-(BORDER-1)-LOBE)*IMG_WIDTH+BORDER-1+LOBE] - buffer[(FILTER_SIZE-(BORDER-1))*IMG_WIDTH+BORDER-1] + buffer[(FILTER_SIZE-(BORDER-1))*IMG_WIDTH+BORDER-1+LOBE]
		//				+ buffer[(BORDER-1)*IMG_WIDTH+(FILTER_SIZE-(BORDER-1)-LOBE)] - buffer[(BORDER-1)*IMG_WIDTH+(FILTER_SIZE-(BORDER-1))] - buffer[(BORDER-1+LOBE)*IMG_WIDTH+(FILTER_SIZE-(BORDER-1)-LOBE)] + buffer[(BORDER-1+LOBE)*IMG_WIDTH+(FILTER_SIZE-(BORDER-1))] - buffer[(FILTER_SIZE-(BORDER-1)-LOBE)*IMG_WIDTH+(FILTER_SIZE-(BORDER-1)-LOBE)] + buffer[(FILTER_SIZE-(BORDER-1)-LOBE)*IMG_WIDTH+(FILTER_SIZE-(BORDER-1))] + buffer[(FILTER_SIZE-(BORDER-1))*IMG_WIDTH+(FILTER_SIZE-(BORDER-1)-LOBE)] - buffer[(FILTER_SIZE-(BORDER-1))*IMG_WIDTH+(FILTER_SIZE-(BORDER-1))];


		float Dxx_9 = A - B - C + D - (E - F - G + H) - (E - F - G + H) - (E - F - G + H);
		//if(r==2&&c==4)std::cerr<<"dxx"<<Dxx_9<<std::endl;
		float Dyy_9 = I - J - K + L - (M - N - O + P) - (M - N - O + P) - (M - N - O + P);
		//if(r==2&&c==4)std::cerr<<"Dyy_9 "<<Dyy_9<<std::endl;
		float Dxy_9 = (Q - R - S + T) + (U - V - W + X) - (Y - Z - Z1 + Z2) - (Z3 - Z4 - Z5 + Z6);
		//if(r==2&&c==4)std::cerr<<"Dxy_9 "<<Dxy_9<<std::endl;

		float inverse_area;
		if(FILTER_SIZE==9)
		{
			inverse_area = inverse_area_9;
		} else if(FILTER_SIZE==15)
		{
			inverse_area = inverse_area_15;
		} else if(FILTER_SIZE==21)
		{
			inverse_area = inverse_area_21;
		} else if(FILTER_SIZE==27)
		{
			inverse_area = inverse_area_27;
		} else if(FILTER_SIZE==39)
		{
			inverse_area = inverse_area_39;
		} else
		{
			inverse_area = inverse_area_51;
		}
		Dxx_9 *= inverse_area;
		Dyy_9 *= inverse_area;
		Dxy_9 *= inverse_area;

		hls::Scalar<1, float> output;
		output.val[0]=(Dxx_9 * Dyy_9 - 0.81f * Dxy_9 * Dxy_9);

//#pragma HLS ALLOCATION instances=CalculateOutput limit=1 function
		//hls::Scalar<1, float> output;
		//output.val[0] = linebuf_51.getval(51, 0);
		//float temp = CalculateOutput(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, Z1, Z2, Z3, Z4, Z5, Z6, inverse_area);
		//output.val[0] = temp;
		//output << (Dxx_9 * Dyy_9 - 0.81f * Dxy_9 * Dxy_9);
		if(count > ((51+1)/2)*(IMG_W+51)+((51+1)/2) - 1)// && c<IMG_W && r<IMG_H)
			out << output;
			//out << Dxx_9 * Dyy_9 - 0.81f * Dxy_9 * Dxy_9;
		//	out << output;

		//if(r==2&&c==4)std::cerr<<count<<" "<<c<<" "<<r<<" "<<M<<" "<<N<<" "<<O<<" "<<P<<std::endl;

		if(col<(IMG_W+51)-1)
			col++;
		else
		{
			col=0;
			row++;
		}
		if(c<(IMG_W+51)-1)
			c++;
		else
		{
			c=0;
			r++;
		}
	}
}

template <int IMG_H, int IMG_W, int IMG_H_OUTPUT, int IMG_W_OUTPUT, int FILTER_SIZE> void test(hls::Mat<MAX_HEIGHT+51, MAX_WIDTH+51, HLS_32FC1> &in, hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1> &out)
{
#pragma HLS inline
	for(int i=0;i<IMG_H+FILTER_SIZE;i++)
	{
		for(int asd=0;asd<IMG_W+FILTER_SIZE;asd++)
		{
			#pragma HLS PIPELINE
			hls::Scalar<1,float> temp;
			in >> temp;
			//temp.val[0] = temp.val[0]/2.0f;
			if(i<IMG_H_OUTPUT&&asd<IMG_W_OUTPUT)
				out << temp;
		}
	}
}

template <int IMG_H, int IMG_W> void passthrough_together(hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1> &in, hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1> &in_, hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1> &out, int filter_size)
{
	for(int i=0;i<IMG_H;i++)
	{
		for(int asd=0;asd<IMG_W;asd++)
		{
			#pragma HLS PIPELINE
			hls::Scalar<1,float> temp;
			hls::Scalar<1, float> temp2;
			in >> temp;
			in_ >> temp2;

			temp.val[0] = temp.val[0]/2.0f*filter_size;
			temp2.val[0] = temp2.val[0]/4.0f*filter_size;

			if(filter_size==9)
			{
				out << temp;
			}
			else
			{
				out << temp2;
			}
		}
	}
}

template <int IMG_H, int IMG_W> void passthrough(hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1> &in, hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1> &out)
{
#pragma HLS inline
	for(int i=0;i<IMG_H;i++)
	{
		for(int asd=0;asd<IMG_W;asd++)
		{
			#pragma HLS PIPELINE
			hls::Scalar<1,float> temp;
			in >> temp;
			temp.val[0] = temp.val[0]/2.0f;
			out << temp;
		}
	}
}

template <int IMG_H, int IMG_W> void passthrough_2(hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1> &in, hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1> &out)
{
#pragma HLS inline
	for(int i=0;i<IMG_H;i++)
	{
		for(int asd=0;asd<IMG_W;asd++)
		{
			#pragma HLS PIPELINE
			hls::Scalar<1,float> temp;
			in >> temp;
			temp.val[0] = temp.val[0]/4.0f;
			out << temp;
		}
	}
}

#define IMAGE_WIDTH 640
#define IMAGE_HEIGHT 480
#define IMAGE_FILTER 9

void function_1(hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1> &in, hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1> &out, int rows, int cols, int filter_size)
{
	//hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1> img_0(rows,cols);
	hls::Mat<MAX_HEIGHT+51, MAX_WIDTH+51, HLS_32FC1> img_1(rows+51,cols+51);
	hls::Mat<MAX_HEIGHT+51, MAX_WIDTH+51, HLS_32FC1> img_12(rows+51,cols+51);
	//hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1> img_2(rows,cols);

	#pragma HLS dataflow
	PadImage<IMAGE_HEIGHT, IMAGE_WIDTH, 51>(in, img_1);//PadImage<IMAGE_HEIGHT, IMAGE_WIDTH, 51>(img_0, img_1);

	int FILTER_SIZE;
		if(filter_size==9)
		{
			FILTER_SIZE=9;
		} else if(filter_size==15)
		{
			FILTER_SIZE=15;
		} else if(filter_size==21)
		{
			FILTER_SIZE=21;
		} else if(filter_size==27)
		{
			FILTER_SIZE=27;
		} else if(filter_size==39)
		{
			FILTER_SIZE=39;
		} else {
			FILTER_SIZE=51;
		}
	FilterTest<IMAGE_HEIGHT, IMAGE_WIDTH>(img_1, img_12, FILTER_SIZE);
	test<IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_HEIGHT, IMAGE_WIDTH, 51>(img_12,out);
}
/*
void function_12(hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1> &in, hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1> &out, int rows, int cols)
{
#pragma HLS INLINE off
#pragma HLS dataflow
	passthrough_2<IMAGE_HEIGHT, IMAGE_WIDTH>(in, out);
}

void function_2(hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1> &in, hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1> &out, int rows, int cols)
{
#pragma HLS INLINE off
#pragma HLS dataflow
	passthrough<IMAGE_HEIGHT, IMAGE_WIDTH>(in, out);
}
*/
template<int IMG_H, int IMG_W> void function_3(hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1> &in, hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1> &in2, hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1> &out, int filter_size)
{
	for(int i=0;i<IMG_H;i++)
	{
		for(int asd=0;asd<IMG_W;asd++)
		{
			#pragma HLS PIPELINE
			hls::Scalar<1,float> temp1;
			hls::Scalar<1, float> temp2;
			hls::Scalar<1, float> output;

			in >> temp1;
			in2 >> temp2;
/*
			if(filter_size>9)
				output.val[0] = temp1.val[0]*filter_size;
			else
				output.val[0] = temp2.val[0]*filter_size;
*/
			if(filter_size>9)
				out << temp1;
			else
				out << temp2;
		}
	}
}
/*
float resize(hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1> &querypatch, hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1> &scaledtrain)
{
	hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1> scaledquery(scaledtrain.rows, scaledtrain.cols);
	Resize_Test(querypatch, scaledquery, querypatch.rows, querypatch.cols, scaledtrain.rows, scaledtrain.cols);

	//ap_fixed<64,32,AP_RND> acc=0;
	float acc=0.0f;
	float res;

	for(int i4=0;i4<scaledquery.rows*scaledquery.cols;i4++)
	{
		#pragma HLS pipeline
		hls::Scalar<1, float> tmp, tmp2;
		scaledquery >> tmp;
		scaledtrain >> tmp2;
		float asd = tmp.val[0] - tmp2.val[0];
		acc += asd*asd;
	}

	float result_acc = hls::sr_cast<float>(acc);

	result_acc = hls::sqrtf(result_acc);
	res=acc;

	return res;
}
*/
float function3(hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1> &query, hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1> &training)
{
#pragma HLS inline
	//float acc=0.0f;
	ap_fixed<64,32,AP_RND> acc=0;
	float res;

	for(int i=0;i<MAX_HEIGHT;i++)
	{
		if(i>=query.rows)
			break;
		for(int asd=0;asd<MAX_WIDTH;asd++)
		{
			if(asd>=query.cols)
				break;
			#pragma HLS PIPELINE
			#pragma HLS LOOP_FLATTEN off
			hls::Scalar<1,float> temp1;
			hls::Scalar<1, float> temp2;
			hls::Scalar<1, float> output;

			query >> temp1;
			training >> temp2;

			float temp = temp1.val[0] - temp2.val[0];
			acc += (ap_fixed<64,32,AP_RND>)(temp*temp);
		}
	}

	res = hls::sqrtf(acc);

	return res;
}

 float image_filter(AXI_STREAM& input_stream, AXI_STREAM& input2, int rows, int cols, int rows2, int cols2) {
    #pragma HLS INTERFACE axis port=input_stream bundle=bus_input_axis
    #pragma HLS INTERFACE axis port=input2 bundle=bus_input2_axis
    #pragma HLS INTERFACE s_axilite port=rows2 bundle=control_bus
	#pragma HLS INTERFACE s_axilite port=cols2 bundle=control_bus
    #pragma HLS INTERFACE s_axilite port=rows bundle=control_bus
    #pragma HLS INTERFACE s_axilite port=cols bundle=control_bus
    #pragma HLS INTERFACE s_axilite port=return bundle=control_bus

	 hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1> img_0(rows,cols);
	 hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1> img_0_1(rows,cols);
	 hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1> img_resized(rows2,cols2);
	 hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1> img_0_2(rows2,cols2);
	 hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1> img_2_1(rows,cols);
	 hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1> img_2_2(rows,cols);
	 hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1> img_2(rows,cols);
	 float res = 1e+37;
#pragma HLS stream depth=20000 variable=img_0_2.data_stream
//#pragma HLS stream depth=8 variable=img_0_2.data_stream
//#pragma HLS stream depth=20000 variable=img_0_1.data_stream
//#pragma HLS stream depth=20000 variable=img_resized.data_stream
#pragma HLS dataflow
	 std::cout<<"here"<<std::endl;
	hls::AXIvideo2Mat(input_stream, img_0_1);
	std::cout<<"here2"<<std::endl;
	hls::AXIvideo2Mat(input2, img_0_2);
	//hls::Duplicate(img_0, img_0_1, img_0_2);
	//passthrough<IMAGE_HEIGHT, IMAGE_WIDTH>(img_0_1, img_2_1);
	std::cout<<"here3"<<std::endl;
	Resize_Test(img_0_1, img_resized, rows, cols, rows2, cols2);
	//passthrough_2<IMAGE_HEIGHT, IMAGE_WIDTH>(img_0_2, img_2_2);
	res=function3(img_resized, img_0_2);
	//hls::Mat2AXIvideo(img_2, output_stream);
	return res;
 }

















