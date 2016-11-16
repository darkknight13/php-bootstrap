<?php
namespace Bootstrap;

class BootstrapBase{
    private $tag;
    private $value;
    private $attributes;
    public function __construct($tag, $value = '', $attributes = array()) {
        $this->tag = $tag;
        $this->value = $value;
        $this->attributes = $attributes;
    }
    static public function initiate($tag, $value = '', $attributes = array()){
        return new self($tag, $value, $attributes);
    }
    public function attributes($attributes) {
        if (empty($this->attributes)) {
            $this->attributes = $attributes;
        }
        return $this;
    }
    public function value($value) {
        if (empty($this->value)) {
            $this->value = $value;
        }
        return $this;
    }
    public function generate() {
        $item['content'] = $this->value;
        $item['attributes'] = $this->attributes;
        $processed = $this->preprocess($item);
        return $this->wrapWithTag($this->tag, $processed['content'], $processed['class'], $processed['id'], $processed['style'], $processed['attr']);
    }
    public function wrapWithTag($tag, $str, $class = '', $id = '', $style = '', $attr = array()) {
        $html = '<' . $tag . ' class="' . $class . '" style="' . $style . '" id="' . $id . '"' . $this->addAttributeFromArray($attr) . '>';
        if (!$this->emptyTag($tag)) {
            $html .= $str . '</' . $tag . '>';
        }
        return $html;
    }
    public function emptyTag($tag){
        $empty_tag_list = array('input');
        if(in_array($tag, $empty_tag_list)){
            return true;
        }
    }
    protected function preprocess($item) {
        $class = $this->split_remove($item['attributes'], 'class', ' ');
        $id = $this->split_remove($item['attributes'], 'id');
        $style = $this->split_remove($item['attributes'], 'style');
        $attributes = $item['attributes'];
        $content = $item['content'];
        return array(
            'content' => $content, 
            'class' => $class, 
            'id' => $id, 
            'style' => $style, 
            'attr' => $attributes
        );
    }
    protected function split_remove(&$item, $index, $implode = false) {
        $value = isset($item[$index]) ? $item[$index] : '';
        unset($item[$index]);
        if ($implode != false && is_array($value)) {
            return implode($implode, $value);
        }
        return $value;
    }
    public function mergerAttributes($index,$merger){
        if(!empty($this->attributes[$index]) && is_array($this->attributes[$index]) && is_array($merger)){
            $this->attributes[$index] = $this->mergeAttributesArray($this->attributes[$index],$merger);
        } else {
            $this->attributes[$index] = $merger;
        }
        return $this;
    }
    public function mergerRootAttributes($merger){
        if(!empty($this->attributes) && is_array($this->attributes) && is_array($merger)){
            $this->attributes = $this->mergeAttributesArray($this->attributes,$merger);
        } else {
            $this->attributes= $merger;
        }
        return $this;
    }
    public function mergeAttributesArray( array $primary, array $input ) {
        foreach( $primary as $key => $value ) {
            if(is_array($value)) {
                if(isset($input[$key])){
                    if(is_array($input[$key])){
                        $input_value = implode(' ',$input[$key]);
                    } else {
                        $input_value = $input[$key];
                    }
                    $primary[$key] = array($input_value,implode(' ',$primary[$key]));
                }
            } else {
                if(isset($input[$key])){
                    $primary[$key] = $input[$key].' '.$value;
                }
            }
            unset($input[$key]);
        }
        foreach ($input as $key => $value){
            $primary[$key] = $value;
        }
        return $primary;
    }
    public function addAttributeFromArray($attr = array()) {
        $attributes = '';
        if (!empty($attr)) {
            foreach ($attr as $key => $value) {
                $property = $key;
                $attributes .= ' ' . $property . '="' . $value . '"';
            }
        }
        return $attributes;
    }
}