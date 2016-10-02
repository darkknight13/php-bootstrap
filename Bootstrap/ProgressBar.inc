<?php

namespace Bootstrap;

require_once 'BootstrapBase.inc';
class ProgressBar {
    private $id;
    private $progress_bar_class = 'progress';
    private $current_progress_bar;
    private $progress_bar = array();

    public function __construct($id) {
        $this->id = $id;
    }

    public function add_bar($percentage, $attributes = array()) {
        if (!empty($this->current_progress_bar)) {
            $this->progress_bar[] = $this->current_progress_bar;
            $this->current_progress_bar = NULL;
        }
        $this->current_progress_bar = array(
            'percentage' => $percentage, 
            'attributes' => $attributes
        );
        $this->current_progress_bar['value'] = $percentage . '%';
        $this->current_progress_bar['show_value'] = false;
        return $this;
    }

    public function attributes($attributes) {
        if (empty($this->current_progress_bar['attributes'])) {
            $this->current_progress_bar['attributes'] = $attributes;
        }
        return $this;
    }

    public function type($type) {
        if (in_array($type, array(
            'default', 
            'primary', 
            'success', 
            'info', 
            'warning', 
            'danger'
        ))) {
            $this->current_progress_bar['type'] = $type;
        }
        return $this;
    }

    public function showtext($text = '') {
        if (!empty($text)) {
            $this->current_progress_bar['value'] = $text;
        }
        $this->current_progress_bar['show_value'] = true;
        return $this;
    }

    public function state($state = '') {
        if (in_array($state, array(
            'active', 
            'disabled'
        ))) {
            $this->current_progress_bar['state'] = $state;
        }
        return $this;
    }

    public function striped($flag = true) {
        $this->current_progress_bar['striped'] = $flag;
        return $this;
    }

    public function limit($now, $min = 0, $max = 100) {
        $this->current_progress_bar['attributes']['aria-valuenow'] = $now;
        $this->current_progress_bar['attributes']['aria-valuemin'] = $min;
        $this->current_progress_bar['attributes']['aria-valuemax'] = $max;
        return $this;
    }

    static public function initiate($id) {
        return new self($id);
    }

    public function generate() {
        $bar_html = array();
        $this->progress_bar[] = $this->current_progress_bar;
        foreach ($this->progress_bar as $progress_bar) {
            $class = array();
            $class[] = $this->progress_bar_class . '-bar';
            $bar_attr = array(
                'role' => 'progressbar'
            );
            if (isset($progress_bar['type'])) {
                $class[] = $this->progress_bar_class . '-bar-' . $progress_bar['type'];
            }
            if ($progress_bar['show_value']) {
                $value = $progress_bar['value'];
            }
            if (!empty($progress_bar['state'])) {
                $class[] = $progress_bar['state'];
            }
            if (!empty($progress_bar['striped']) && $progress_bar['striped'] == true) {
                $class[] = $this->progress_bar_class . '-bar-striped';
            }
            $progress_bar['attributes']['style'] = 'width: ' . $progress_bar['percentage'] . '%;' . (isset($progress_bar['attributes']['style']) ? $progress_bar['attributes']['style'] : '');
            $bar_html[] = BootstrapBase::initiate('div')->attributes($progress_bar['attributes'])
                ->mergerAttributes('class', $class)
                ->mergerRootAttributes($bar_attr)
                ->value($value)
                ->generate();
        }
        
        return BootstrapBase::initiate('div')->attributes(array(
            'class' => $this->progress_bar_class
        ))
            ->value(implode('', $bar_html))
            ->generate();
    }
}