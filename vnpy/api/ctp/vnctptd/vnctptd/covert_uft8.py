# encoding: UTF-8

import os

def gbk_to_utf8(input_file, output_file):
    # Load Files
    input_file_opened = open(input_file, 'r', encoding='gbk')
    input_file_read = input_file_opened.read()
    output_file_opened = open(output_file, 'x', encoding='utf-8', newline='\n')
    # Transcode
    print('Transcoding…')
    output_file_opened.write(input_file_read)
    input_file_opened.close()
    output_file_opened.close()
    print('Done.\n')

def main():
    print('Code Page 936 (GBK) to UTF-8 Transcoder\n')
    # Ask the User Which File to Transcode
    while 0 == 0:
        input_file = input('Full file path of GBK file:\n')
        output_file = input('Full file path of utf-8 file:\n')
        gbk_to_utf8(input_file, output_file)

if __name__ == '__main__':
    main()