<?php 
namespace Bootstrap;

class Panel {
    private $id;
    private $header;
    private $body;
    private $footer;
    private $collapsible = false;
    private $html = array();
    private $panel = array();
    public function __construct($id, $class ='default') {
        $this->id = $id;
        if(!in_array($class,array('default','primary','success','info','warning','danger'))){
            $class = 'default';
        }
        $this->panel = array(
            'id' => array(
                'header' => $this->id. '_header',
                'body' => $this->id. '_body',
                'footer' => $this->id . '_footer'
            ),
            'class' => $class
        );
    }
    static public function initiate($id, $class ='default'){
        return new self($id, $class);
    }
    public function add_header($content, $attributes = array()) {
        $this->header = array(
            'content' => $content,
            'attributes' => $attributes
        );
        return $this;
    }
    public function add_body($content, $attributes  = array() ) {
        $this->body = array(
            'content' => $content,
            'attributes' => $attributes
        );
        return $this;
    }
    public function add_footer($content, $attributes  = array()) {
        $this->footer = array(
            'content' => $content,
            'attributes' => $attributes
        );
        return $this;
    }
    public function set_collapsible() {
        $this->collapsible = true;
        return $this;
    }
    public function generate() {
        if(isset($this->header['content'])){
            $class = array();
            $header_html = $this->header['content'];
            if($this->collapsible){
                $collapse_attr = array(
                    'role'=>'button',
                    'data-toggle'=>'collapse',
                    'data-parent'=>'#accordion',
                    'href'=>'#'.$this->panel['id']['body'],
                    'aria-expanded'=>'true',
                    'aria-controls'=> $this->panel['id']['body']
                );
                $header_html = BootstrapBase::initiate('div')->attributes($collapse_attr)->value($header_html)->generate();
            }
            $class[] = 'panel-heading';
            $html[] = BootstrapBase::initiate('div')->attributes($this->header['attributes'])->mergerAttributes('class',$class)->value($header_html)->generate();
        }
        if(isset($this->body['content'])){
            $class = array();
            $class[] = 'panel-body';
            $body = BootstrapBase::initiate('div')->attributes($this->body['attributes'])->mergerAttributes('class',$class)->value($this->body['content'])->generate();
            if($this->collapsible){
                $collapse_attr = array(
                    'id'=>$this->panel['id']['body'],
                    'class'=>'panel-collapse collapse',
                    'role'=>'tabpanel',
                    'aria-labelledby'=> $this->panel['id']['header']
                );
                $body = BootstrapBase::initiate('div')->attributes($collapse_attr)->value($body)->generate();
            }
            $html[] = $body;
            
        }
        if(isset($this->footer['content'])){
            $class = array();
            $class[] = 'panel-footer';
            $html[] = BootstrapBase::initiate('div')->attributes($this->footer['attributes'])->mergerAttributes('class',$class)->value($this->footer['content'])->generate();
        }
        return wrapWithDiv(implode('',$html),'panel panel-'.$this->panel['class']);
    }
}
