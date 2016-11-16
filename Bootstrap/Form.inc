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

class Form {
    private $html;
    private $preprocessed_html = array();
    private $method;
    private $action;
    private $version = 5;
    private $current_element;
    private $wrapper_list = array('div','fieldset','td','panel');
    private $form_elements = array();

    public function __construct($method = 'post', $action = '') {
        $this->method = $method;
        $this->action = $action;
    }
    
    public function add_element($element,$name, $type='', $attributes = array(), $options = array()) {
        if (!empty($this->current_element)) {
            $this->form_elements[] = $this->current_element;
            $this->current_element = NULL;
        }
        $this->current_element = array(
            'element'=>$element,
            'name'=>$name,
            'type'=>$type,
            'attributes' => $attributes,
            'options' => $options,
            'value'=>''
        );
        return $this;
    }
    
    public function wrapWith($type, $attributes = array()){
        if(in_array($type, $this->wrapper_list)){
            
        }
    }
    public function type($type) {
        if (empty($this->current_element['type'])) {
            $this->current_element['type'] = $type;
        }
        return $this;
    }
    
    public function label($label) {
        if (empty($this->current_element['label'])) {
            $this->current_element['label'] = $label;
        }
        return $this;
    }
    
    public function value($value) {
        if (empty($this->current_element['value'])) {
            $this->current_element['value'] = $value;
        }
        return $this;
    }
    
    public function attributes($attributes) {
        if (empty($this->current_element['attributes'])) {
            $this->current_element['attributes'] = $attributes;
        }
        return $this;
    }
    
    static public function initiate($method = 'post', $action = '') {
        return new self($method, $action);
    }
    
    public function generate() {
        $this->form_elements[] = $this->current_element;
        foreach ($this->form_elements as $form_elements){
            $class = array();
            $class[] = 'form-control';
            $form_elements['attributes']['type'] = $form_elements['type'];
            $form_elements['attributes']['name'] = $form_elements['name'];
            if(!empty($form_elements['label'])){
                if(empty($form_elements['attributes']['id'])){
                    $form_elements['attributes']['id'] = 'idFormElement-'.$form_elements['name'];
                }
                $this->preprocessed_html[] = BootstrapBase::initiate('label',$form_elements['label'],array('for'=>$form_elements['attributes']['id']))->generate();
            }
            $this->preprocessed_html[] = BootstrapBase::initiate($form_elements['element'],$form_elements['value'],$form_elements['attributes'])->mergerAttributes('class', $class)->generate();
        }
        return BootstrapBase::initiate('form',implode('', $this->preprocessed_html))->generate();
    }
    
    public function version($version){
        $this->version = $version;
    }
}
