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

class Tab {
    private $bootstrap_tab = array();
    private $html = '';
    private $bootstrap_nav = array();
    private $bootstrap_pane = array();
    
    public function __construct($id) {
        $this->id = $id;
    }
    
    public function add_Tab($title, $content, $title_attributes = array(), $content_attributes = array()){
        $this->bootstrap_tab[] = array(
            'title'=>$title,
            'attributes' => array(
                'title' => $title_attributes, 
                'content' => $content_attributes
            ),
            'content'=>$content
        );
        return $this;
    }
    
    public function generate(){
        $count = 1;
        $active = false;
        foreach($this->bootstrap_tab as $tab){
            $class = array();
            if($count == 1){
                $active = true;
                $class[]= 'active';
            }
            $nav_attr = array(
                'role'=>'presentation'
            );
            if(isset($tab['attributes']['content']['id'])){
                $content_id = $tab['attributes']['content']['id'];
            } else {
                $content_id = $this->id.'_'.$count;
            }
            $content_link_attr = array(
                'href'=>'#'.$content_id,
                'aria-controls'=>$content_id,
                'role'=>'tab',
                'data-toggle'=>'tab'
            );
            $content_link  = BootstrapBase::initiate('a')->attributes($tab['attributes']['title'])->mergerRootAttributes($content_link_attr)->value($tab['title'])->generate();
            $this->bootstrap_nav[] = BootstrapBase::initiate('li')->attributes($nav_attr)->mergerAttributes('class',$class)->value($content_link)->generate();
            $class[]= 'tab-pane';
            $content_attr = array(
                'role'=>'tabpanel',
                'id'=>$content_id
            );
            $this->bootstrap_pane[] = BootstrapBase::initiate('div')->attributes($tab['attributes']['content'])->mergerRootAttributes($content_attr)->mergerAttributes('class',$class)->value($tab['content'])->generate(); 
            $active = false;
            $count++;
        }
        $nav_list = implode('',$this->bootstrap_nav);
        $pane_list = implode('',$this->bootstrap_pane);
        
        return BootstrapBase::initiate('ul',$nav_list,array('class'=>'nav nav-tabs','role'=>'tablist'))->generate().
        BootstrapBase::initiate('div',$pane_list,array('class'=>'tab-content'))->generate();
    }
}
