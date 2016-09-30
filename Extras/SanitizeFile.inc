<?php
const NORMALIZE_STRIP_TAG = 0x1;
const NORMALIZE_LINE_REPLACE = 0x2;
const NORMALIZE_SPECIAL_CHAR_REPLACE = 0x4;
const NORMALIZE_LOWER_CASE = 0x8;
const NORMALIZE_HTML_ENTITY_DECODE = 0x10;
const NORMALIZE_HTML_ENTITIES = 0x10;
const NORMALIZE_EN_FILE = 0x20;
const NORMALIZE_URL_SAFE = 0x40;
const NORMALIZE_REPLACE_SPACE = 0x800;
const NORMALIZE_REPLACE_PERCENTAGE = 0x100;
const NORMALIZE_ALL = 0x200;

class SanitizeFile {
    private $file;
    private $file_location = '';
    private $basename = '';
    private $extension = '';
    private $dotted_extension = '';
    private $filename = '';

    public function __construct($filepath) {
        $this->file = pathinfo($filepath);
        if (!empty($this->file['dirname'])) {
            $this->file_location = $this->file['dirname'];
        }
        if (!empty($this->file['basename'])) {
            $this->basename = $this->file['basename'];
        }
        if (!empty($this->file['extension'])) {
            $this->extension = $this->file['extension'];
            $this->dotted_extension = '.' . $this->file['extension'];
        }
        if (!empty($this->file['filename'])) {
            $this->filename = $this->file['filename'];
        }
    }

    public function sanitizeFileName() {
        return $this->normalizeString($this->filename) . $this->dotted_extension;
    }

    public function normalizeString($str = '', $option = NORMALIZE_ALL) {
        if ($option & NORMALIZE_ALL) {
            $all_step = true;
        }
        if ($option & NORMALIZE_STRIP_TAG || $all_step) {
            $str = strip_tags($str);
        }
        if ($option & NORMALIZE_LINE_REPLACE || $all_step) {
            $str = preg_replace('/[\r\n\t ]+/', ' ', $str);
        }
        if ($option & NORMALIZE_SPECIAL_CHAR_REPLACE || $all_step) {
            $str = preg_replace('/[\"\*\/\:\<\>\?\'\|]+/', ' ', $str);
        }
        if ($option & NORMALIZE_LOWER_CASE || $all_step) {
            $str = strtolower($str);
        }
        if ($option & NORMALIZE_HTML_ENTITY_DECODE || $all_step) {
            $str = html_entity_decode($str, ENT_QUOTES, "utf-8");
        }
        if ($option & NORMALIZE_HTML_ENTITIES || $all_step) {
            $str = htmlentities($str, ENT_QUOTES, "utf-8");
        }
        if ($option & NORMALIZE_EN_FILE || $all_step) {
            $str = preg_replace("/(&)([a-z])([a-z]+;)/i", '$2', $str);
        }
        if ($option & NORMALIZE_REPLACE_SPACE || $all_step) {
            $str = str_replace(' ', '-', $str);
        }
        if ($option & NORMALIZE_URL_SAFE || $all_step) {
            $str = rawurlencode($str);
        }
        if ($option & NORMALIZE_REPLACE_PERCENTAGE || $all_step) {
            $str = str_replace('%', '-', $str);
        }
        $str = preg_replace('!-+!', '-', $str);
        return $str;
    }

    static public function initiate($filepath) {
        return new self($filepath);
    }
}