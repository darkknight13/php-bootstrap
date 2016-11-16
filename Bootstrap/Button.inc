<?php
/**
 * Copyright 2016 Carnival Technologies
 *
 * Licensed under the GNU AFFERO GENERAL PUBLIC LICENSE v3.0 (the "License");
 *
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.gnu.org/licenses/agpl.txt
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
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