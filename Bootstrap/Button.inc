<?php
namespace Bootstrap;
require_once 'BootstrapBase.inc';

class Button {
    private $value;
    private $element;
    private $attributes;
    private $type;
    private $size;
    private $state;
    private $base_element;
    private $button_class = 'btn';
    
    public function __construct($value, $element ='button') {
        $this->value = $value;
        if(!in_array($element,array('a','input','button'))){
            $this->element = 'button';
        } else {
            $this->element = $element;
        }
        $this->type = 'default';
        $this->baseElement = new BootstrapBase($this->element);
    }
    public function type($type){
        if(in_array($type,array('default','primary','success','info','warning','danger'))){
            $this->type = $type;
        }
        return $this;
    }
    public function size($size){
        if(in_array($size,array('xs','sm','lg'))){
            $this->size = $size;
        }
        return $this;
    }
    public function state($state=''){
        if(in_array($state,array('active','disabled'))){
            $this->state = $state;
        }
        return $this;
    }
    public function attributes($attributes){
        if (empty($this->attributes)) {
            $this->attributes = $attributes;
        }
        return $this;
    }
    public function generate(){
        $class = array();
        $class[] = $this->button_class;
        $class[] = $this->button_class.'-'.$this->type;
        if(!empty($this->size)){
            $class[] = $this->button_class.'-'.$this->size;
        }
        if(!empty($this->state)){
            $class[] = $this->state;
        }
        return BootstrapBase::initiate($this->element)->attributes($this->attributes)->mergerAttributes('class',$class)->value($this->value)->generate();
    }
    static public function initiate($value, $element ='button'){
        return new self($value, $element);
    }
}