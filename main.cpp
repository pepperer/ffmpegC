#include <iostream>

void testLog();

void listFiles();

void getMediaInfo();

void writeFile();

extern "C" {
#include <static/Hello.h>
#include <libavutil/log.h>
#include <libavformat/avio.h>
#include <libavformat/avformat.h>
}

int main(int argc, char *argv[]) {
//    Hello hi;
//    printf("hello world %d\n", hi.a);
//    hi.print();
//
//    printf(" ----\n");
//    printf("%d\n", argc);
//    printf(argv[0]);
//    printf(" ----\n");
//    printf(argv[1]);


    testLog();

//    writeFile();

//    getMediaInfo();
    return 0;
}

void testLog() {
    av_log_set_level(AV_LOG_DEBUG);
    av_log(NULL, AV_LOG_INFO, "hello ffmpeg11\n");
}


void writeFile() {
    int err_code;

    char *src_filename = "con.txt";
    AVIOContext *avio_ctx = NULL;

    unsigned char buf[] = "hello world!";

    av_log_set_level(AV_LOG_DEBUG);

    err_code = avio_open(&avio_ctx, src_filename, AVIO_FLAG_WRITE);

    if (err_code < 0) {
        av_log(NULL, AV_LOG_DEBUG, "Could not open file %s\n", src_filename);
        return;
    }

    avio_write(avio_ctx, buf, 6);
    err_code = avio_close(avio_ctx);
    if (err_code < 0) {
        av_log(NULL, AV_LOG_DEBUG, "close err %s\n", av_err2str(err_code));
    }
}

/**
 *
 */
void getMediaInfo() {
    int err_code;
    char errors[1024];
    AVFormatContext *avFormatContext = NULL;

    char *src_filename = "/Users/zhishui/Downloads/black.mp4";

    av_register_all();

    err_code = avformat_open_input(&avFormatContext, src_filename, NULL, NULL);
    if (err_code < 0) {
        av_strerror(err_code, errors, 1024);
        fprintf(stderr, "Could not open source file %s, %d(%s)\n", src_filename, err_code, errors);
        return;
    }

    err_code = avformat_find_stream_info(avFormatContext, NULL);
    if (err_code < 0) {
        av_strerror(err_code, errors, 1024);
        fprintf(stderr, "avformat_find_stream_info %s, %d(%s)\n", src_filename, err_code, errors);
        return;
    }

    av_dump_format(avFormatContext, 0, src_filename, 1);

    avformat_close_input(&avFormatContext);
}
